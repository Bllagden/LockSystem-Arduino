#include "func.h"

Servo SERVO;

bool isOpenDoor() {
  return digitalRead(GERKON_PIN);
}

/*Проверка нажатия кнопки. Если нажата - return True*/
bool isButton() {
  return !digitalRead(BTN_PIN);
}

/*Проверка таймаута с помощью millis*/
bool checkTimeout(uint32_t curTime, uint16_t CONST_TIMEOUT) {
  return millis() - curTime >= CONST_TIMEOUT;
}

/*Блокирует замок*/
void lock() {
  SERVO.attach(SERVO_PIN);
  //uint8_t degrees = 180;
  //for (uint8_t i = 0; i < 20; i++) {
  //degrees -= 9;
  //SERVO.write(degrees);
  //delay(50);
  //}
  SERVO.write(0);
  delay(1000);
  SERVO.detach();
  Serial.println("Servo closed the door");
}

/*Разблокирует замок*/
void unlock() {
  SERVO.attach(SERVO_PIN);
  //uint8_t degrees = 0;
  //for (uint8_t i = 0; i < 20; i++) {
  //degrees += 9;
  //SERVO.write(degrees);
  //delay(50);
  //}
  SERVO.write(90);
  delay(1000);
  SERVO.detach();
  Serial.println("Servo opened the door");
}