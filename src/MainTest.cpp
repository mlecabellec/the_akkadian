/*
 * Main.cpp
 *
 *  Created on: 30 août 2020
 *      Author: vortigern
 */

#include "Main.hpp"

namespace akkadian
{
	using namespace akkadian;
	using namespace std;

	Main::Main()
	{
		// TODO Auto-generated constructor stub
	}

	Main::~Main()
	{
		// TODO Auto-generated destructor stub
	}

	bool Main::init()
	{

		std::cout << "Main::init()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "Main::init(), service is not in READY or UNNOWN state\r\n";
			return false;
		}

		//this->_cameraHandlerCenter = new CameraHandler("/dev/video0",1280,720);
		this->_cameraHandlerCenter = new CameraHandler(CONFIG_CAMERAS.find("POSITION_CENTER")->second);
		this->_cameraHandlerBlue = new CameraHandler(CONFIG_CAMERAS.find("POSITION_BLUE_SIDE")->second);
		this->_cameraHandlerYellow = new CameraHandler(CONFIG_CAMERAS.find("POSITION_YELLOW_SIDE")->second);
		this->_weatherVaneDetectorBlue = new WeatherVaneDetector(CONFIG_CAMZONES.find("weatherVaneFromBlueSide")->second);
		this->_weatherVaneDetectorYellow = new WeatherVaneDetector(CONFIG_CAMZONES.find("weatherVaneFromYellowSide")->second);

		this->_serialService = new SerialService(CONFIG_MAIN_SERIAL_PORT);
		this->_gpioService = new GpioService() ;

		bool isOk = this->_cameraHandlerCenter->init();
		isOk = isOk ? this->_cameraHandlerBlue->init() : false;
		isOk = isOk ? this->_cameraHandlerYellow->init() : false;
		isOk = isOk ? this->_serialService->init() : false;

		isOk = isOk ? this->_weatherVaneDetectorBlue->init() : false;
		isOk = isOk ? this->_weatherVaneDetectorYellow->init() : false;

		isOk = isOk ? this->_cameraHandlerBlue->addFrameHandler(this->_weatherVaneDetectorBlue) : false;
		isOk = isOk ? this->_cameraHandlerYellow->addFrameHandler(this->_weatherVaneDetectorYellow) : false;

		isOk = isOk ? this->_weatherVaneDetectorBlue->addListener(this->_serialService) : false;
		isOk = isOk ? this->_weatherVaneDetectorYellow->addListener(this->_serialService) : false;

		isOk = isOk ? this->_gpioService->init() : false;


		this->_status = ServiceStatusEnum::READY;

		if (isOk)
		{
			std::cout << "Main::init(), isOk = true\r\n";
			this->_status = ServiceStatusEnum::READY;
		}
		else
		{
			std::cout << "Main::init(), isOk = FALSE\r\n";
			//this->_status = ServiceStatusEnum::FAILED;
		}

		return isOk;
	}

	bool Main::start()
	{
		std::cout << "Main::start()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "Main::start(), service is not in READY state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STARTING;
		this->_thread = new thread(&Main::run, this);

		bool isOk = this->_cameraHandlerCenter->start();
		isOk = isOk ? this->_cameraHandlerBlue->start() : false;
		isOk = isOk ? this->_cameraHandlerYellow->start() : false;

		isOk = isOk ? this->_weatherVaneDetectorBlue->start() : false;
		isOk = isOk ? this->_weatherVaneDetectorYellow->start() : false;

		isOk = isOk ? this->_serialService->start() : false;

		if (isOk)
		{
			std::cout << "Main::start(), isOk = true\r\n";
			//this->_status = ServiceStatusEnum::STARTING;
		}
		else
		{
			std::cout << "Main::start(), isOk = FALSE\r\n";
			//this->_status = ServiceStatusEnum::FAILED;
		}

		return isOk;
	}
	bool Main::stop()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::RUNNING)
		{
			std::cout << "Main::stop(), service is not in RUNNING state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STOPPING;
		bool isOk = this->_cameraHandlerCenter->stop();
		isOk = isOk ? this->_cameraHandlerBlue->stop() : false;
		isOk = isOk ? this->_cameraHandlerYellow->stop() : false;

		isOk = isOk ? this->_weatherVaneDetectorBlue->stop() : false;
		isOk = isOk ? this->_weatherVaneDetectorYellow->stop() : false;
		isOk = isOk ? this->_serialService->stop() : false;
		isOk = isOk ? this->_gpioService->stop() : false;

		//this->_thread->join();

		return isOk;
	}

	void Main::run()
	{
		if (this->_status == ServiceStatusEnum::STARTING)
		{
			this->_status = ServiceStatusEnum::RUNNING;
		}

		int numCycle = 0 ;
		std::cout << "Main::run(), going in run() loop...\r\n";
		while (this->_status == ServiceStatusEnum::RUNNING)
		{
			numCycle++;
			if( numCycle > 100000)
			{
				//this->stop();
				//std::exit(0);
			}
			try
			{
				std::this_thread::sleep_for(2000ms);
			}
			catch (const std::exception &e)
			{

				//TODO: log
			}
		}
		std::cout << "Main::run(), leaving in the loop\r\n";

	}

} /* namespace akkadian */

int main(int argc, char **argv)
{

	akkadian::Main *main = new akkadian::Main();

	main->init();
	main->start();
	main->getThread()->join();

	return 0;
}
