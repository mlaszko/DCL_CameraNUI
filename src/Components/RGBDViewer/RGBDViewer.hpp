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
	 * Event handler function.
	 */
	void onNewRGBDImage();

	/// Event handler.
	Base::EventHandler <RGBDViewer> h_onNewRGBDImage;

	/// Input data stream containing colour.
	Base::DataStreamIn <cv::Mat> in_rgb;
	
	/// Input data stream containing depth.
	Base::DataStreamIn <cv::Mat> in_depth;
	

};

} //: namespace RGBDViewer
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("RGBDViewer", Processors::RGBDViewer::RGBDViewer)

#endif /* RGBDVIEWER_HPP_ */
