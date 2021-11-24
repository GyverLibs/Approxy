#include <Approxy.h>

// двумерный массив, у столбцов одинаковый тип
int tab[][2] = {
  {0, 0},
  {10, 1},
  {20, 5},
  {30, 12},
  {40, 20},
  {50, 30},
  {60, 39},
  {70, 47},
  {80, 54},
  {90, 58},
  {100, 60},
};

Approxy2D<int> table(tab, 11);

void setup() {
  Serial.begin(9600);

  // выводим
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
