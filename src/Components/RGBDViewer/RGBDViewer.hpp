/*!
 * \file
 * \brief 
 * \author tkornuta,,,
 */

#ifndef RGBDVIEWER_HPP_
#define RGBDVIEWER_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Processors {
namespace RGBDViewer {

/*!
 * \class RGBDViewer
 * \brief RGBDViewer processor class.
 *
 * RGBDViewer processor.
 */
class RGBDViewer: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	RGBDViewer(const std::string & name = "RGBDViewer");

	/*!
	 * Destructor
	 */
	virtual ~RGBDViewer();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

	/*!
	 * Callback called when filename is changed
	 */
	void onFilenameChanged(const std::string & old_filename,
			const std::string & new_filename);

	/*!
	 * Callback called when dir is changed
	 */
	void onDirChanged(const std::string & old_dir, const std::string & new_dir);

	/*!
	 * Event handler function - refreshes windows with RGBD image.
	 */
	void onNewRGBDImage();

	/*!
	 * Event handler function - for saving RGBD image to file.
	 */
	void onSaveRGBDImage();

	/// Event handler for refreshing.
	Base::EventHandler <RGBDViewer> h_onNewRGBDImage;

	/// Event handler for saving.
	Base::EventHandler <RGBDViewer> h_onSaveRGBDImage;

	/// Input data stream containing colour.
	Base::DataStreamIn <cv::Mat> in_rgb;
	
	/// Input data stream containing depth.
	Base::DataStreamIn <cv::Mat> in_depth;

	/// RGB image to be drawn/saved.
	cv::Mat rgb_img;

	/// Depth image to be drawn/saved.
	cv::Mat depth_img;
	
	Base::Property<std::string> filename;
	Base::Property<std::string> dir;

};

} //: namespace RGBDViewer
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("RGBDViewer", Processors::RGBDViewer::RGBDViewer)

#endif /* RGBDVIEWER_HPP_ */
