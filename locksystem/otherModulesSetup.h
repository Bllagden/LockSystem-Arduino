#ifndef _MODULESSETUP_H_
#define _MODULESSETUP_H_


#include <Arduino.h>
#include "pins.h"

void other_modules_Setup() {
  pinMode(BUZZER_PIN, INPUT);  // Зуммер

  pinMode(GERKON_PIN, INPUT);      // Геркон, установка вывода на вход
  digitalWrite(GERKON_PIN, HIGH);  // Включение внутреннего подтягивающего резистора

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);  // RGB светодиод
  //pinMode(BLU_LED_PIN, OUTPUT);

  pinMode(BTN_PIN, INPUT_PULLUP);  //Кнопка
}


#endif