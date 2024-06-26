[![latest](https://img.shields.io/github/v/release/GyverLibs/Approxy.svg?color=brightgreen)](https://github.com/GyverLibs/Approxy/releases/latest/download/Approxy.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/Approxy.svg)](https://registry.platformio.org/libraries/gyverlibs/Approxy)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Approxy?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Approxy
Линейный аппроксиматор
- Аппроксимирует таблицу для получения промежуточных результатов
- Работа со всеми типами данных
- Режим PROGMEM для хранения таблицы во Flash

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **Approxy** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/Approxy/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


## Как это работает
Допустим, есть некая *нелинейная* зависимость одного значения от другого, например сигнал с датчика 
(столбец X, горизонтальная ось) и соответствующее ему физическое значение (столбец Y, вертикальная ось):
![scheme](/docs/p1.png)

Чтобы получить показания с такого неприятного условного датчика, нужно знать соответствие между ними и сигналом с датчика. 
Если это соответствие не описывается простым математическим уравнением (прямая пропорциональность, полином, экспонента, логарифм и так далее), то 
можно откалибровать (оттарировать) датчик по нескольким точкам, построив таблицу. Можно сделать это с шагом в условную единицу, 
получив большую таблицу соответствий для любых значений. А можно сделать несколько точек и вычислять промежуточные значения, 
считая зависимость между ними линейной. Это позволит в несколько раз уменьшить размер таблицы, не сильно потеряв в точности. Пример с 11 точками (оранжевая линия):
![scheme](/docs/p2.png)

Именно это и делает данная библиотека.

<a id="init"></a>
## Инициализация
### Раздельные столбцы (два массива)
```cpp
Approxy<typeX, typeY> table(arrayX, arrayY, size);
Approxy<typeX, typeY, AP_PGM> table(arrayX, arrayY, size);

// typeX и typeY - типы данных массивов. Могут быть разными
// arrayX и arrayY - сами массивы
// size - размер таблицы (количество строк)
// AP_PGM - режим PROGMEM
```
### Общая таблица (двумерный массив)
```cpp
Approxy2D<type> table(array, size);
Approxy2D<type, AP_PGM> table(array, size);

// type - тип данных массива
// array - самимассив
// size - размер таблицы (количество строк)
// AP_PGM - режим PROGMEM
```

<a id="usage"></a>
## Использование
```cpp
float table.get(float x);   // получить аппроксимированное значение
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
// раздельная таблица, массивы в оперативной памяти
#include <Approxy.h>

// таблица, столбцы могут быть разных типов
int tx[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
float ty[] = {0, 1, 5, 12, 20, 30, 39, 47, 54, 58, 60};

Approxy<int, float> table(tx, ty, 11);

void setup() {
  Serial.begin(9600);

  // выводим
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
```

```cpp
// общая таблица в PROGMEM
#include <Approxy.h>

// двумерный массив, у столбцов одинаковый тип
const int tab[][2] PROGMEM = {
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

Approxy2D<int, AP_PGM> table(tab, 11);

void setup() {
  Serial.begin(9600);

  // выводим
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
```

<a id="versions"></a>
## Версии
- v1.0
- v1.1 - исправлен баг в Approxy2D в режиме RAM

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
