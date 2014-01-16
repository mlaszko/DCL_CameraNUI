/*!
 * \file
 * \brief
 * \author tkornuta,,,
 */

#include <memory>
#include <string>

#include "RGBDViewer.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace RGBDViewer {

RGBDViewer::RGBDViewer(const std::string & name) :
		Base::Component(name)  {

}

RGBDViewer::~RGBDViewer() {
}

void RGBDViewer::prepareInterface() {
	CLOG(LTRACE) << name() << "::onFinish";
	// Register data streams, events and event handlers HERE!
	registerStream("in_rgb", &in_rgb);
	registerStream("in_depth", &in_depth);

	h_onNewRGBDImage.setup(this, &RGBDViewer::onNewRGBDImage);
	registerHandler("onNewRGBDImage", &h_onNewRGBDImage);
	addDependency("onNewRGBDImage", &in_rgb);
	addDependency("onNewRGBDImage", &in_depth);

}

bool RGBDViewer::onInit() {
	CLOG(LTRACE) << name() << "::onInit";
	// Create windows.
	cv::namedWindow("RGB");
	cv::namedWindow("Depth");
	return true;
}

bool RGBDViewer::onFinish() {
	CLOG(LTRACE) << name() << "::onFinish";
	// Destroy windows.
	cv::destroyWindow("RGB");
	cv::destroyWindow("Depth");
	return true;
}

bool RGBDViewer::onStop() {
	return true;
}

bool RGBDViewer::onStart() {
	return true;
}

void RGBDViewer::onNewRGBDImage() {
	CLOG(LTRACE) << name() << "::onNewRGBDImage";
	// Refresh images.
	cv::imshow("RGB", in_rgb.read());
	cv::imshow("Depth", in_depth.read());
	cv::waitKey(2);
}


} //: namespace RGBDViewer
} //: namespace Processors
