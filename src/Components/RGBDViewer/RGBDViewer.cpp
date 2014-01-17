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
		Base::Component(name),
		dir("save.directory", boost::bind(&RGBDViewer::onDirChanged, this, _1, _2), "./"),
		filename("save.filename", boost::bind(&RGBDViewer::onFilenameChanged, this, _1, _2), "image")
{
	registerProperty( filename);
	registerProperty( dir);
}

RGBDViewer::~RGBDViewer() {
}

void RGBDViewer::prepareInterface() {
	CLOG(LTRACE) << name() << "::onFinish";
	// Register data streams, events and event handlers HERE!
	registerStream("in_rgb", &in_rgb);
	registerStream("in_depth", &in_depth);
	
	// Refresh.
	h_onNewRGBDImage.setup(this, &RGBDViewer::onNewRGBDImage);
	registerHandler("onNewRGBDImage", &h_onNewRGBDImage);
	addDependency("onNewRGBDImage", &in_rgb);
	addDependency("onNewRGBDImage", &in_depth);

	// Save.
	h_onSaveRGBDImage.setup(this, &RGBDViewer::onSaveRGBDImage);
	registerHandler("onSaveRGBDImage", &h_onSaveRGBDImage);
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
	rgb_img = in_rgb.read();
	depth_img = in_depth.read();
	cv::imshow("RGB", rgb_img);
	cv::imshow("Depth", depth_img);
	cv::waitKey(2);
}

void RGBDViewer::onSaveRGBDImage() {
	CLOG(LTRACE) << name() << "::onSaveRGBDImage";

	std::time_t rawtime;
	std::tm* timeinfo;
	char buffer [80];

	// Generate time postfix.
	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);
	std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);

	// Change compression to lowest.
        vector<int> param;
	param.push_back(CV_IMWRITE_PNG_COMPRESSION);
	param.push_back(0); // MAX_MEM_LEVEL = 9 

	try {
		// Save rgb image.
		if (rgb_img.empty()) {
			LOG(LWARNING) << name() << ": rgb image empty";
		} else {
			std::string tmp_name = std::string(dir) + std::string("/") + std::string(filename) + "_" + buffer + std::string("_rgb.png");
			imwrite(tmp_name, rgb_img, param);
			CLOG(LINFO) << "RGB image saved to file " << tmp_name <<std::endl;
		}
		// Save depth image.
		if (depth_img.empty()) {
			LOG(LWARNING) << name() << ": depth image empty";
		} else {
			std::string tmp_name = std::string(dir) + std::string("/") + std::string(filename) + "_" + buffer + std::string("_depth.png");
			cv::Mat depthf  (cv::Size(640,480),CV_16UC1);
        		depth_img.convertTo(depthf, CV_16UC1, 1);//255.0/2048.0);
			imwrite(tmp_name, depthf);//, param);
			CLOG(LINFO) << "Depth image saved to file " << tmp_name <<std::endl;
		}
	} catch (std::exception &ex) {
		CLOG(LERROR) << "CvWindow::onSaveRGBDImage failed: " << ex.what() << "\n";
	}
}

void RGBDViewer::onFilenameChanged(const std::string & old_filename,
		const std::string & new_filename) {
	filename = new_filename;
	CLOG(LTRACE) << "onFilenameChanged: " << std::string(filename) << std::endl;
}

void RGBDViewer::onDirChanged(const std::string & old_dir,
		const std::string & new_dir) {
	dir = new_dir;
	CLOG(LTRACE) << "onDirChanged: " << std::string(dir) << std::endl;
}


} //: namespace RGBDViewer
} //: namespace Processors
