#ifndef _VALUES_H_
#define _VALUES_H_


#include <Arduino.h>

#define CLEAR_TIMEOUT 3000  // Очистка замка
#define LOCK_TIMEOUT 2000   // Время до блокировки замка после закрытия двери в мс
#define RFID_TIMEOUT 500
#define BT_RFID_TIMEOUT 1500

#define MAX_TAGS 3       // Максимальное количество хранимых меток - ключей
#define EE_START_ADDR 0  // Начальный адрес в EEPROM
#define EE_KEY 100       // Ключ EEPROM, для проверки на первое вкл.

#define DECLINE 0  // Отказ
#define SUCCESS 1  // Успешно
#define SAVED 2    // Новая метка записана
#define DELITED 3  // Метка удалена


#endif