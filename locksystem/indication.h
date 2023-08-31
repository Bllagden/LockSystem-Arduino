#ifndef _INDICATE_H_
#define _INDICATE_H_


#include <Arduino.h>
#include "pins.h"
#include "values.h"

void ledSetup(bool state);
void indicate(uint8_t signal);


#endif