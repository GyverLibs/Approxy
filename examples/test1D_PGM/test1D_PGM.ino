#include <Approxy.h>

// таблица, столбцы могут быть разных типов
// float не работает в этом режиме
const int tx[] PROGMEM = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
const int ty[] PROGMEM = {0, 1, 5, 12, 20, 30, 39, 47, 54, 58, 60};

Approxy<int, int, AP_PGM> table(tx, ty, 11);

void setup() {
  Serial.begin(9600);

  // выводим
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
