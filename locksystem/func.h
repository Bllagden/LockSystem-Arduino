#ifndef _FUNC_H_
#define _FUNC_H_


#include <Arduino.h>
#include <Servo.h>
#include "pins.h"

bool isOpenDoor();
bool isButton();
bool checkTimeout(uint32_t curTime, uint16_t CONST_TIMEOUT);
void lock();
void unlock();


#endif