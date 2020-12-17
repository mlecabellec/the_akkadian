/*
 * Main.h
 *
 *  Created on: 30 août 2020
 *      Author: vortigern
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "CameraHandler.hpp"
#include "WeatherVaneDetector.hpp"
#include "AkkadianService.hpp"
#include "GpioService.hpp"
#include "SerialService.hpp"
#include "Configuration.hpp"
#include <chrono>
#include <string>
#include <thread>
#include <cstdlib>

#include <boost/log/trivial.hpp>

namespace akkadian
{
	using namespace std;
	using namespace akkadian;

	class Main : public AkkadianService
	{
	public:
		Main();
		virtual ~Main();


		bool init();
		bool start();
		bool stop();
		bool reset();
		void run();


		CameraHandler *_cameraHandlerCenter;
		CameraHandler *_cameraHandlerYellow;
		CameraHandler *_cameraHandlerBlue;

		WeatherVaneDetector * _weatherVaneDetectorBlue ;
		WeatherVaneDetector * _weatherVaneDetectorYellow ;

		SerialService *_serialService ;
		GpioService *_gpioService ;
		
	private:
	};

} /* namespace akkadian */

#endif /* MAIN_H_ */
