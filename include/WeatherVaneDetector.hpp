/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef WEATHERVANEDETECTOR_H_
#define WEATHERVANEDETECTOR_H_

#include <thread>
#include <mutex>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
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

#include <ios>
#include <iostream>
#include <fstream>

namespace akkadian
{

	using namespace std;

	class WeatherVaneDetector : public akkadian::AkkadianService, public FrameHandler, public AkkadianEventProducer<Game2020WeatherVanePosition *>
	{
	public:
		WeatherVaneDetector(int x, int y, int width, int height, std::string name); //
		WeatherVaneDetector(SimpleRectZoneInCamera zone);
		virtual ~WeatherVaneDetector();

		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();
		bool processFrame(std::shared_ptr<cv::Mat> frame, std::string sourceDevice = "", std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now()) override;

	private:
		std::chrono::milliseconds _cycleDuration = 107ms;
		std::queue<std::shared_ptr<Mat>> *_frames;
		int _x;
		int _y;
		int _width;
		int _height;

		std::map<std::chrono::time_point<std::chrono::system_clock>, cv::Scalar> *_history;
		std::chrono::milliseconds _maxHistory = 100s;
		std::chrono::milliseconds _recentHistory = 4s;


		std::ofstream _csvFileStream;
	};

} /* namespace akkadian */

#endif /* CAMERAHANDLER_H_ */
