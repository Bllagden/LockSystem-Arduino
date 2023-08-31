//#include <SPI.h>
//#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include "pins.h"
#include "values.h"
#include "otherModulesSetup.h"
#include "func.h"
#include "indication.h"
#include "rfid.h"

SoftwareSerial BT_Serial(BT_RX, BT_TX);
bool BT_Auto_Block_Flag = true;
bool BT_Unlock_Flag = false;
String BT_Command = "";

bool Locked_Flag = false;  // Флаг состояния замка

void setup() {
  Serial.begin(115200);
  BT_Serial.begin(9600);
  SPI.begin();
  rfid_Init();
  other_modules_Setup();

  // Полная очистка при включении при зажатой кнопке
  uint32_t start = millis();                   // Отслеживание длительного удержания кнопки после включения
  bool needClear = 0;                          // Чистим флаг на стирание
  while (isButton()) {                         // Пока кнопка нажата
    if (checkTimeout(start, CLEAR_TIMEOUT)) {  // Встроенный таймаут на 3 секунды
      needClear = true;                        // Ставим флаг стирания при достижении таймаута
      indicate(DELITED);                       // Подаем сигнал удаления
      break;                                   // Выходим из цикла
    }
  }

  // Инициализация EEPROM
  if (needClear or EEPROM.read(EE_START_ADDR) != EE_KEY) {                 // при первом включении или необходимости очистки ключей
    for (uint16_t i = 0; i < EEPROM.length(); i++) EEPROM.write(i, 0x00);  // Чистим всю EEPROM
    EEPROM.write(EE_START_ADDR, EE_KEY);                                   // Пишем байт-ключ
  }

  // Начальное состояние замка
  if (isOpenDoor()) {
    ledSetup(SUCCESS);
    Locked_Flag = false;
    unlock();
  } else {
    ledSetup(DECLINE);
    Locked_Flag = true;
    lock();
  }
  //printEEPROM();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // проверка двери на ее открытость с помощью геркона
  static uint32_t openDoorTime;
  if (isOpenDoor()) {
    openDoorTime = millis();
  }

  // блокировка двери
  if (!Locked_Flag and BT_Auto_Block_Flag and checkTimeout(openDoorTime, LOCK_TIMEOUT)) {
    ledSetup(DECLINE);
    lock();
    Locked_Flag = true;
  }

  // открытие замка по нажатию кнопки изнутри или из приложения Bluetooth
  //if (Locked_Flag and (isButton() or BT_Unlock_Flag))
  if ((Locked_Flag and isButton()) or (Locked_Flag and BT_Unlock_Flag)) {
    indicate(SUCCESS);
    unlock();
    openDoorTime = millis();
    Locked_Flag = false;
    BT_Unlock_Flag = false;
  }

  // если замок закрыт и поднесение RFID метки
  static uint32_t rfidCurTime = 0;
  if (Locked_Flag and isReadTag()) {
    if (checkCurrentTag()) {
      indicate(SUCCESS);
      unlock();
      Locked_Flag = false;
      openDoorTime = millis();
    } else if (checkTimeout(rfidCurTime, RFID_TIMEOUT)) {
      indicate(DECLINE);
    }
    rfidCurTime = millis();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Bluetooth, прием комадны
  if (BT_Serial.available() > 0) {
    while (BT_Serial.available() > 0) {
      BT_Command += (char)BT_Serial.read();
      delay(2);  // ЗАДЕРЖКА. Без неё работает некорректно!
    }

    if ((BT_Command.equals("admin_open_lock_command") or BT_Command.equals("client_open_lock_command")) and (Locked_Flag)) {
      BT_Unlock_Flag = true;
    } else if (BT_Command.equals("client_fail_open_lock_command")) {
      indicate(DECLINE);
    } else if (BT_Command.equals("auto_block_off_command")) {
      BT_Auto_Block_Flag = false;
    } else if (BT_Command.equals("auto_block_on_command")) {
      BT_Auto_Block_Flag = true;
    }
    BT_Command = "";
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////