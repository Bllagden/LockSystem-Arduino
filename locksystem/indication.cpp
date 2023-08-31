#include "indication.h"

// Устанавливаем состояние светодиодов
void ledSetup(bool state) {
  if (state) {  // Зеленый
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {  // Красный
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
}

// Звуковой сигнал + лед
void indicate(uint8_t signal) {
  ledSetup(signal);  // Лед
  switch (signal) {  // Выбираем сигнал
    case DECLINE:
      //Serial.println("DECLINE");
      for (uint8_t i = 0; i < 2; i++) {
        pinMode(BUZZER_PIN, OUTPUT);
        analogWrite(BUZZER_PIN, 100);
        delay(300);
        pinMode(BUZZER_PIN, INPUT);
        delay(100);
      }
      return;
    case SUCCESS:
      //Serial.println("SUCCESS");
      pinMode(BUZZER_PIN, OUTPUT);
      analogWrite(BUZZER_PIN, 890);
      delay(330);
      pinMode(BUZZER_PIN, INPUT);
      return;
    case SAVED:
      Serial.println("SAVED");
      for (uint8_t i = 0; i < 2; i++) {
        pinMode(BUZZER_PIN, OUTPUT);
        analogWrite(BUZZER_PIN, 890);
        delay(330);
        pinMode(BUZZER_PIN, INPUT);
        delay(100);
      }
      return;
    case DELITED:
      Serial.println("DELITED");
      for (uint8_t i = 0; i < 3; i++) {
        pinMode(BUZZER_PIN, OUTPUT);
        analogWrite(BUZZER_PIN, 890);
        delay(330);
        pinMode(BUZZER_PIN, INPUT);
        delay(100);
      }
      return;
  }
}