#ifndef _RFID_H_
#define _RFID_H_


#include <Arduino.h>
#include <MFRC522.h>
#include "pins.h"

void rfid_Init();
bool isReadTag();
bool checkCurrentTag();
bool compareUIDs(uint8_t size, uint8_t *key1, uint8_t *key2);
void rfidRebootTimer();


#endif