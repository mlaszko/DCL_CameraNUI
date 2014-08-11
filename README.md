DCL_CameraNUI - DisCODe Component Library
=========================================

Description
-----------

Provides communication with Kinect sensor.

Available parameters:

- <lib> can be set to 'freenect' (default) or 'opencv'

- <depth_mode> 'rawMap'(default) - which gives unmodified data and - normalized, disparityMap, dM32f, pointCloud, valid - dM32f states for disparity map 32bit float and valid yields a mask of valid pixels

- <camera_mode> 'rgb' or 'gray'

- <skip_stop> prevents kinect from shutdown, which often takes long time and can be omitted for debugging purposes

Example is provided with the code

Dependencies
------------

- OpenKinect/libfreenect with all its dependencies as described here http://openkinect.org/wiki/Getting_Started 

- OpenCv (tested with version 2.3.1) (compiled with WITH_OPENNI option if you want to aquire signal via OpenCv highgui functions)

- Check WITH_OPENNI option in cmake accordingly here

Tasks
------------
Kinect acquisition:
   * __KinectDisplay__ - Simple Kinect viewer, shows possible depth conversions. 
   * __KinectRGBDViewer__ - Displays RGB image with the associated depth map, allows saving of both color and depth to png files with a proper data format.
   * __KinectRGBXYZViewer__ - Displays RGB image with Depth map. Allows saving of RGB and XYZ (image containing XYZ coordinages) to files (png and yaml respectivelly). 
    
RGB-D sequences from files:   
   * __RGBDSequenceViewer__ - Displays two windows - with RGB and depth images.


Developers
----------
Michal Lisicki

Maciej Stefańczyk

Maintainer
----------
Tomasz Kornuta

