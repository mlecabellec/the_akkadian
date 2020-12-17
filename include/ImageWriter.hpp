/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef ImageWriter_H_
#define ImageWriter_H_

#include <thread>
#include <mutex>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "AkkadianService.hpp"
#include "AkkadianEvents.hpp"
#include "FrameHandler.hpp"
#include "Configuration.hpp"
#include "Models.hpp"

#include <list>
#include <chrono>
#include <limits>
#include <algorithm>

namespace akkadian
{

	using namespace std;


	class ImageWriter : public akkadian::AkkadianService, public FrameHandler
	{
	public:
		ImageWriter(SimpleRectZoneInCamera zone );
		virtual ~ImageWriter();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();
		bool processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice = "", std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now()) override;

	private:
		std::chrono::milliseconds _cycleDuration = 1517ms;
		std::queue<std::shared_ptr<Mat>> *_frames;
		int _x;
		int _y;
		int _width;
		int _height;
        std::string _name ;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */
