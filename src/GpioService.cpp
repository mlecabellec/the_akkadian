/*
 * GpioService.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "GpioService.hpp"

namespace akkadian
{

	using namespace akkadian;
	using namespace std;
	using namespace cv;

	GpioService::GpioService() : AkkadianService(), AkkadianEventListener<Game2020WeatherVanePosition>(std::string("GpioService"))
	{
		// TODO Auto-generated constructor stub
	}

	GpioService::~GpioService()
	{
		// TODO Auto-generated destructor stub
	}

	bool GpioService::init()
	{
		std::cout << "GpioService::init()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::UNKNOWN && this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "GpioService::init(), not in READY or UNKNOWN state\r\n";
			return false;
		}

		wiringPiSetup();

		pinMode(GPIO_SIDESENSING_YELLOW_SIDE_HIGH_PIN, OUTPUT);
		pinMode(GPIO_SIDESENSING_YELLOW_SIDE_LOW_PIN, OUTPUT);
		pinMode(GPIO_SIDESENSING_YELLOW_SIDE_SENSOR_PIN, INPUT);

		pinMode(GPIO_SIDESENSING_BLUE_SIDE_HIGH_PIN, OUTPUT);
		pinMode(GPIO_SIDESENSING_BLUE_SIDE_LOW_PIN, OUTPUT);
		pinMode(GPIO_SIDESENSING_BLUE_SIDE_SENSOR_PIN, INPUT);

		digitalWrite(GPIO_SIDESENSING_YELLOW_SIDE_HIGH_PIN, HIGH);
		digitalWrite(GPIO_SIDESENSING_YELLOW_SIDE_LOW_PIN, LOW);
		digitalWrite(GPIO_SIDESENSING_BLUE_SIDE_HIGH_PIN, HIGH);
		digitalWrite(GPIO_SIDESENSING_BLUE_SIDE_LOW_PIN, LOW);

		this->_status = ServiceStatusEnum::READY;
		return true;
	}

	bool GpioService::start()
	{
		std::cout << "GpioService::start()\r\n";
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::READY)
		{
			std::cout << "GpioService::start(), service is not in READY state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STARTING;

		//std::cout << "GpioService::start(), checking if device is opened...\r\n";

		this->_thread = new thread(&GpioService::run, this);

		return true;
	}
	bool GpioService::stop()
	{
		std::lock_guard<std::mutex> lock(this->_mutex);
		if (this->_status != ServiceStatusEnum::RUNNING)
		{
			std::cout << "GpioService::stop(), not in RUNNING state\r\n";
			return false;
		}

		this->_status = ServiceStatusEnum::STOPPING;

		return true;
	}

	bool GpioService::processEvent(AkkadianEvent<Game2020WeatherVanePosition> *event)
	{
		std::cout << "GpioService::processEvent(AkkadianEvent<Game2020WeatherVanePosition> *event), received event\r\n";

		return true;
	}

	void GpioService::run()
	{
		if (this->_status == ServiceStatusEnum::STARTING)
		{
			this->_status = ServiceStatusEnum::RUNNING;
		}

		std::cout << "GpioService::run(), going in the loop\r\n";
		while (this->_status == ServiceStatusEnum::RUNNING)
		{
			try
			{

				std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();
				std::chrono::time_point<std::chrono::system_clock> t1 = t0;
				t1 += this->_cycleDuration;

				//-----------------------------------------------------------
				//Akkadian position detection

				int readOnBlueSideSwitch = digitalRead(GPIO_SIDESENSING_BLUE_SIDE_SENSOR_PIN);
				int readOnYellowSideSwitch = digitalRead(GPIO_SIDESENSING_YELLOW_SIDE_SENSOR_PIN);

				std::cout << "GpioService::run(), readOnBlueSideSwitch = " << readOnBlueSideSwitch << "\r\n";
				std::cout << "GpioService::run(), readOnYellowSideSwitch = " << readOnYellowSideSwitch << "\r\n";

				Game2020AkkadianPositionENum detectedPosition = Game2020AkkadianPositionENum::AKKADIAN_POSITION_UNKNOWN;

				if (readOnBlueSideSwitch == HIGH && readOnYellowSideSwitch == LOW)
				{
					std::cout << "GpioService::run(), akkadian position = AKKADIAN_POSITION_YELLOW_SIDE\r\n";
					detectedPosition = Game2020AkkadianPositionENum::AKKADIAN_POSITION_YELLOW_SIDE;
				}
				else if (readOnBlueSideSwitch == LOW && readOnYellowSideSwitch == HIGH)
				{
					std::cout << "GpioService::run(), akkadian position = AKKADIAN_POSITION_BLUE_SIDE\r\n";
					detectedPosition = Game2020AkkadianPositionENum::AKKADIAN_POSITION_BLUE_SIDE;
				}
				else
				{
					std::cout << "GpioService::run(), akkadian position = AKKADIAN_POSITION_UNKNOWN\r\n";
					detectedPosition = Game2020AkkadianPositionENum::AKKADIAN_POSITION_UNKNOWN;
				}

				Game2020AkkadianPosition *pos = new Game2020AkkadianPosition();
				pos->_akkadianPosition = detectedPosition;
				AkkadianEvent<Game2020AkkadianPosition *> *evt = new AkkadianEvent<Game2020AkkadianPosition *>(pos);

				for (std::map<std::string, AkkadianEventListener<Game2020AkkadianPosition *> *>::iterator it = this->getListeners()->begin(); it != this->getListeners()->end(); ++it)
				{
					it->second->processEvent(evt);
				}

				delete evt;
				delete pos;

				//-----------------------------------------------------------

				std::this_thread::sleep_until(t1);
			}
			catch (const std::exception &e)
			{

				//TODO: log
			}
		}
		std::cout << "GpioService::run(), leaving in the loop\r\n";
	}

} /* namespace akkadian */
