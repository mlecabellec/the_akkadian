/*
 * CameraHandler.h
 *
 *  Created on: 16 oct. 2020
 *      Author: vortigern
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <thread>
#include <mutex>
#include <string>

#include "opencv.hpp"
#include <iostream>
#include "AkkadianService.hpp"
#include <list>
#include <chrono>

namespace akkadian
{

    using namespace std;
    using namespace cv;

    enum EventStatusEnum : uint8_t
    {
        EVENTSTATUS_UNKNOWN = 0x00,
        EVENTSTATUS_NEW = 0x01,
        EVENTSTATUS_PARTIALLY_PROCESSED = 0x02,
        EVENTSTATUS_PROCESSED = 0x03
    };

    template <class T>
    class AkkadianEvent
    {
    public:
        AkkadianEvent(T data)
        {
            this->_data = data;
            this->_status = EventStatusEnum::EVENTSTATUS_NEW;
        };
        ~AkkadianEvent(){

        };

        T _data;
        EventStatusEnum _status;
    };

    template <class T>
    class AkkadianEventListener
    {
    public:
        AkkadianEventListener(std::string id)
        {
            this->_id = id;
        };
        ~AkkadianEventListener(){};

        virtual bool processEvent(AkkadianEvent<T> *event)
        {
            return false;
        };

        std::string _id;
    };

    template <class T>
    class AkkadianEventProducer
    {
    public:
        AkkadianEventProducer()
        {
            this->_listeners = new std::map<std::string, AkkadianEventListener<T> *>();
        };
        ~AkkadianEventProducer()
        {
            delete this->_listeners;
        };

        bool addListener(AkkadianEventListener<T> *listener)
        {
            this->_listeners->insert_or_assign(listener->_id , listener);
            return true;
        };

        bool removeListener(AkkadianEventListener<T> *listener)
        {
            auto it =  this->_listeners->find(listener->_id) ;

            if(it != this->_listeners->end())
            {
                this->_listeners->erase(it);
                return true;
            }else
            {
                return false ;
            }
            
        };

        std::map<std::string, AkkadianEventListener<T> *> * getListeners()
        {
            return this->_listeners ;
        }


        std::map<std::string, AkkadianEventListener<T> *> *_listeners;
    };

} /* namespace akkadian */

#endif /* FRAMEHANDLER_H_ */
