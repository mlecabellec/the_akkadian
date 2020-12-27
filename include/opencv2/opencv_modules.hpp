// Then the optional modules are checked
#ifdef HAVE_OPENCV_CALIB3D
#include "opencv2/calib3d.hpp"
#endif
#ifdef HAVE_OPENCV_FEATURES2D
#include "opencv2/features2d.hpp"
#endif
#ifdef HAVE_OPENCV_DNN
#include "opencv2/dnn.hpp"
#endif
#ifdef HAVE_OPENCV_FLANN
#include "opencv2/flann.hpp"
#endif

#define HAVE_OPENCV_IMGCODECS
#define HAVE_OPENCV_IMGPROC
#define HAVE_OPENCV_ML
#define HAVE_OPENCV_OBJDETECT
#define HAVE_OPENCV_PHOTO
#define HAVE_OPENCV_STITCHING
#define HAVE_OPENCV_VIDEO
#define HAVE_OPENCV_VIDEOIO
