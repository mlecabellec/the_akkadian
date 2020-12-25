/*
 * AkkadianService.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef AKKADIANSERVICE_H_
#define AKKADIANSERVICE_H_

#include <cstdint>
#include <thread>
#include <mutex>
#include <iostream>

namespace akkadian
{

	enum ServiceStatusEnum : uint8_t
		{
		UNKNOWN = 0x00,
		READY = 0x01,
		STARTING = 0x02,
		RUNNING = 0x04,
		STOPPING = 0x08,
		STOPPED = 0x10,
		FAILED = 0x20
	};

	class AkkadianService
	{
	public:
		AkkadianService();
		virtual ~AkkadianService();

		bool init();
		bool start();
		bool stop();
		bool reset();

		ServiceStatusEnum getStatus();

		std::thread *getThread() const
		{
			return _thread;
		}



		ServiceStatusEnum _status;
		std::thread *_thread;
		std::mutex _mutex;

	protected:
	private:
	};

} /* namespace akkadian */

#endif /* AKKADIANSERVICE_H_ */
