/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "CameraNUI.hpp"
#include "Common/Logger.hpp"

#include <opencv2/imgproc/imgproc.hpp>

namespace Processors {
namespace CameraNUI {

CameraNUI::CameraNUI(const std::string & name) :
		Base::Component(name),
		sync("sync", true),
		m_camera_info(640, 480, 319.5, 239.5, 525, 525) {

	LOG(LTRACE)<< "Hello CameraNUI\n";
	registerProperty(sync);
}

CameraNUI::~CameraNUI() {
	LOG(LTRACE)<< "Good bye CameraNUI\n";
}

void CameraNUI::prepareInterface() {

	// Register data streams
	registerStream("out_img", &outImg);
	registerStream("out_depth", &outDepthMap);
	registerStream("out_camera_info", &camera_info);



	h_onNextImage.setup(this, &CameraNUI::onNextImage);
	registerHandler("onNextImage", &h_onNextImage);
	addDependency("onNextImage", NULL);
}

bool CameraNUI::onInit() {
	LOG(LTRACE)<< "CameraNUI::initialize\n";

	cameraFrame = cv::Mat(cv::Size(640,480),CV_8UC3,cv::Scalar(0));
	depthFrame = cv::Mat(cv::Size(640,480),CV_16UC1);

	return true;
}

bool CameraNUI::onFinish() {
	LOG(LTRACE)<< "CameraNUI::finish\n";
	return true;
}

void CameraNUI::onNextImage() {
	short *depth = 0;
	char *rgb = 0;
	uint32_t ts;
	int ret;

	// retrieve color image
	ret = freenect_sync_get_video((void**)&rgb, &ts, 0, FREENECT_VIDEO_RGB);
	cv::Mat tmp_rgb(480, 640, CV_8UC3, rgb);
	cv::cvtColor(tmp_rgb, cameraFrame, CV_RGB2BGR);

	// retrieve depth image
	ret = freenect_sync_get_depth((void**)&depth, &ts, 0, FREENECT_DEPTH_REGISTERED);
	cv::Mat tmp_depth(480, 640, CV_16SC1, depth);
	tmp_depth.copyTo(depthFrame);

	// write data to output streams
	outImg.write(cameraFrame);
	outDepthMap.write(depthFrame);

	camera_info.write(m_camera_info);
}

bool CameraNUI::onStop() {
	freenect_sync_stop();
	return true;
}

bool CameraNUI::onStart() {
	return true;
}

} //: namespace CameraNUI
} //: namespace Processors
