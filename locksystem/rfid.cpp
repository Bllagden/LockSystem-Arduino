#include "rfid.h"

static MFRC522 rfid(SS_PIN, RST_PIN);  // Обьект RFID

/*Инициализация модуля rfid*/
void rfid_Init() {
  rfid.PCD_Init();
}

/*Проверка RFID метки. Если поднесена и успешно считана - return True*/
bool isReadTag() {
  return rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial();
}

/*Проверка RFID метки путем сравнения ее с подходящей. Если равны - return True*/
bool checkCurrentTag() {
  uint8_t size = rfid.uid.size;
  uint8_t *curKey = rfid.uid.uidByte;
  uint8_t trueKey[] = { 0xD3, 0x20, 0x8B, 0x1D };
  return compareUIDs(size, curKey, trueKey);
}

/*Сравнение двух массивов. Если равны - return True*/
bool compareUIDs(uint8_t size, uint8_t *key1, uint8_t *key2) {
  for (uint8_t i = 0; i < size; i++) {
    if (key1[i] != key2[i])
      return false;
  }
  return true;
}

// Перезагружаем RFID каждые 0.5 сек (для надежности)
void rfidRebootTimer() {
  static uint32_t rfidRebootTimer = millis();
  if (millis() - rfidRebootTimer > 500) {
    rfidRebootTimer = millis();
    digitalWrite(RST_PIN, HIGH);
    delay(1);
    digitalWrite(RST_PIN, LOW);
    rfid.PCD_Init();
  }
}