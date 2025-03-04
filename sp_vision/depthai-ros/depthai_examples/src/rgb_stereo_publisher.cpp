
#include <cstdio>
#include <iostream>

#include "ros/ros.h"
// #include "utility.hpp"
#include <camera_info_manager/camera_info_manager.h>

#include <functional>

#include "sensor_msgs/Image.h"

// Inludes common necessary includes for development using depthai library
#include <depthai_bridge/BridgePublisher.hpp>
#include <depthai_bridge/ImageConverter.hpp>

#include "depthai/depthai.hpp"



dai::Pipeline createPipeline(bool lrcheck, bool extended, bool subpixel, int confidence, int LRchecktresh, std::string resolution) {
    dai::Pipeline pipeline;
    auto controlIn = pipeline.create<dai::node::XLinkIn>();
    auto monoLeft = pipeline.create<dai::node::MonoCamera>();
    auto monoRight = pipeline.create<dai::node::MonoCamera>();
    auto stereo = pipeline.create<dai::node::StereoDepth>();
    auto xoutDepth = pipeline.create<dai::node::XLinkOut>();
    controlIn->setStreamName("control");
    controlIn->out.link(monoRight->inputControl);
    controlIn->out.link(monoLeft->inputControl);

    xoutDepth->setStreamName("depth");

    dai::node::MonoCamera::Properties::SensorResolution monoResolution;
    if(resolution == "720p") {
        monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_720_P;
    } else if(resolution == "400p") {
        monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_400_P;
    } else if(resolution == "800p") {
        monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_800_P;
    } else if(resolution == "480p") {
        monoResolution = dai::node::MonoCamera::Properties::SensorResolution::THE_480_P;
    } else {
        ROS_ERROR("Invalid parameter. -> monoResolution: %s", resolution.c_str());
        throw std::runtime_error("Invalid mono camera resolution.");
    }

    // MonoCamera
    monoLeft->setResolution(monoResolution);
    monoLeft->setBoardSocket(dai::CameraBoardSocket::LEFT);
    monoRight->setResolution(monoResolution);
    monoRight->setBoardSocket(dai::CameraBoardSocket::RIGHT);

    // StereoDepth
    stereo->initialConfig.setConfidenceThreshold(confidence);
    stereo->setRectifyEdgeFillColor(0);  // black, to better see the cutout
    stereo->initialConfig.setLeftRightCheckThreshold(LRchecktresh);

    stereo->setLeftRightCheck(lrcheck);
    stereo->setExtendedDisparity(extended);
    stereo->setSubpixel(subpixel);
    // stereo->setDepthAlign(dai::CameraBoardSocket::RGB);
    // stereo->setDepthAlign(dai::CameraBoardSocket::RGB);
    // // Link plugins CAM -> STEREO -> XLINK
    monoLeft->out.link(stereo->left);
    monoRight->out.link(stereo->right);
    stereo->depth.link(xoutDepth->input);
    


    // Color camers steream setup -------->
    auto camRgb = pipeline.create<dai::node::ColorCamera>();
    auto xoutRgb = pipeline.create<dai::node::XLinkOut>();
    xoutRgb->setStreamName("rgb");
    camRgb->setBoardSocket(dai::CameraBoardSocket::RGB);
    camRgb->setResolution(dai::ColorCameraProperties::SensorResolution::THE_1080_P);
    camRgb->setInterleaved(true);
    // camRgb->setIspScale(rgbScaleNumerator, rgbScaleDinominator);

    controlIn->out.link(camRgb->inputControl);
    camRgb->isp.link(xoutRgb->input);

// ctrl.setManualExposure(expTime, sensIso);
    // Link plugins CAM -> XLINK

    return pipeline;
}

template <typename T>
static inline void getParamWithWarning(ros::NodeHandle& pnh, const char* key, T val) {
    bool gotParam = pnh.getParam(key, val);
    if(!gotParam) {
        std::stringstream ss;
        ss << val;
        ROS_WARN("Could not find param '%s' on node '%s'. Defaulting to '%s'", key, pnh.getNamespace().c_str(), ss.str().c_str());
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "rgb_stereo_node");
    ros::NodeHandle pnh("~");

    std::string tfPrefix = "dai";
    std::string camera_param_uri;
    std::string monoResolution = "720p";

    bool lrcheck, extended, subpixel, manualExposure;
    int confidence = 200;
    int LRchecktresh = 5;
    int expTime ;
    int sensIso ;

    getParamWithWarning(pnh, "tf_prefix", tfPrefix);
    getParamWithWarning(pnh, "camera_param_uri", camera_param_uri);
    getParamWithWarning(pnh, "lrcheck", lrcheck);
    getParamWithWarning(pnh, "extended", extended);
    getParamWithWarning(pnh, "subpixel", subpixel);
    getParamWithWarning(pnh, "confidence", confidence);
    getParamWithWarning(pnh, "LRchecktresh", LRchecktresh);
    getParamWithWarning(pnh, "manualExposure", manualExposure);
    getParamWithWarning(pnh, "expTime", expTime);
    getParamWithWarning(pnh, "sensIso", sensIso);
    // std::cout<<"aaaaaaaaa"<<expTime;


    dai::Pipeline pipeline = createPipeline(lrcheck, extended, subpixel, confidence, LRchecktresh, monoResolution);
    dai::Device device(pipeline);
    auto calibrationHandler = device.readCalibration();
    // auto monoHFOV = np.deg2rad(calibrationHandler.getFov(dai.CameraBoardSocket.LEFT))
    auto controlQueue = device.getInputQueue("control");
       // Apply camera controls
    // auto controlQueue = device->getInputQueue("control");
    // bool manualExposure = true;
    // Set manual exposure
    if(manualExposure) {
        dai::CameraControl ctrl;
        ctrl.setManualExposure(expTime, sensIso);
        controlQueue->send(ctrl);
    }

    auto stereoQueue = device.getOutputQueue("depth", 30, false);
    auto previewQueue = device.getOutputQueue("rgb", 30, false);
    // auto previewQueue = device.getOutputQueue("video", 1, false);

    

    bool latched_cam_info = true;
    std::string stereo_uri = camera_param_uri + "/" + "right.yaml";
    std::string color_uri = camera_param_uri + "/" + "color.yaml";

    dai::rosBridge::ImageConverter depthConverter(tfPrefix + "_right_camera_optical_frame", true);
    auto rgbCameraInfo = depthConverter.calibrationToCameraInfo(calibrationHandler, dai::CameraBoardSocket::RGB, 1280, 720);

    //     while (ros::ok())
    // {



    dai::rosBridge::BridgePublisher<sensor_msgs::Image, dai::ImgFrame> depthPublish(stereoQueue,
                                                                                    pnh,
                                                                                    std::string("stereo/depth"),
                                                                                    std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
                                                                                              &depthConverter,  // since the converter has the same frame name
                                                                                                                // and image type is also same we can reuse it
                                                                                              std::placeholders::_1,
                                                                                              std::placeholders::_2),
                                                                                    30,
                                                                                    rgbCameraInfo,
                                                                                    "stereo");

    dai::rosBridge::ImageConverter rgbConverter(tfPrefix + "_rgb_camera_optical_frame", true);
    dai::rosBridge::BridgePublisher<sensor_msgs::Image, dai::ImgFrame> rgbPublish(previewQueue,
                                                                                  pnh,
                                                                                  std::string("color/image"),
                                                                                  std::bind(&dai::rosBridge::ImageConverter::toRosMsg,
                                                                                            &rgbConverter,  // since the converter has the same frame name
                                                                                                            // and image type is also same we can reuse it
                                                                                            std::placeholders::_1,
                                                                                            std::placeholders::_2),
                                                                                  30,
                                                                                  rgbCameraInfo,
                                                                                  "color");

    depthPublish.addPublisherCallback();  // addPublisherCallback works only when the dataqueue is non blocking.
    rgbPublish.addPublisherCallback();
    // We can add the rectified frames also similar to these publishers.
    // Left them out so that users can play with it by adding and removing

    ros::spin();

    return 0;
}
