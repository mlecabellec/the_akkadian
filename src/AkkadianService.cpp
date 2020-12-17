/*
 * AkkadianService.cpp
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#include "AkkadianService.hpp"

namespace akkadian
{

	AkkadianService::AkkadianService()
	{
		// TODO Auto-generated constructor stub
		this->_status = ServiceStatusEnum::UNKNOWN;
	}

	AkkadianService::~AkkadianService()
	{
		// TODO Auto-generated destructor stub
	}

	bool AkkadianService::init()
	{
		return false;
	}

	bool AkkadianService::start()
	{
		return false;
	}

	bool AkkadianService::stop()
	{
		return false;
	}

	bool AkkadianService::reset()
	{
		return false;
	}

	ServiceStatusEnum AkkadianService::getStatus()
	{
		return this->_status;
	}

} /* namespace akkadian */
