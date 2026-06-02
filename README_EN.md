This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/Approxy.svg?color=brightgreen)](https://github.com/GyverLibs/Approxy/releases/latest/download/Approxy.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/Approxy.svg)](https://registry.platformio.org/libraries/gyverlibs/Approxy)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/Approxy?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# Approxy
Linear approximator
- Approximates the table to obtain intermediate results
- Working with all types of data
- PROGMEM mode for storing a table in Flash

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **Approxy** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/Approxy/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

## How it works.
Suppose there is some *nonlinear* dependence of one value on another, for example, a signal from a sensor.
(column X, horizontal axis) and corresponding physical value (column Y, vertical axis):
![scheme](/docs/p1.png)

To get readings from such an unpleasant conditional sensor, you need to know the correspondence between them and the signal from the sensor.
If this correspondence is not described by a simple mathematical equation (direct proportionality, polynomial, exponent, logarithm, etc.), then
You can calibrate (set) the sensor to several points by constructing a table. You can do this with a step into a conventional unit.
Get a large table of correspondences for any values. And you can make a few points and calculate the intermediate values.
The relationship between them is linear. This will allow you to reduce the size of the table several times, without much loss in accuracy. Example with 11 points (orange line):
![scheme](/docs/p2.png)

This is what this library does.

<a id="init"></a>
## Initialization
### Separate columns (two arrays)
```cpp
Approxy<typeX, typeY> table(arrayX, arrayY, size);
Approxy<typeX, typeY, AP_PGM> table(arrayX, arrayY, size);

// TypeX and TypeY are data types. It can be different.
// arrayX and arrayY - the arrays themselves
// Size - table size (number of rows)
// AP PGM - PROGMEM mode
```
### General table (two-dimensional array)
```cpp
Approxy2D<type> table(array, size);
Approxy2D<type, AP_PGM> table(array, size);

// type - data type of array
// array - samassive
// Size - table size (number of rows)
// AP PGM - PROGMEM mode
```

<a id="usage"></a>
## Use of use
```cpp
float table.get(float x);   // approximate
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
// separate table, arrays in memory
#include <Approxy.h>

// table, columns can be of different types
int tx[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
float ty[] = {0, 1, 5, 12, 20, 30, 39, 47, 54, 58, 60};

Approxy<int, float> table(tx, ty, 11);

void setup() {
  Serial.begin(9600);

  // output
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
```

```cpp
// general table in PROGMEM
#include <Approxy.h>

// two-dimensional array, columns have the same type
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

  // output
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - fixes the bug in Approxy2D in RAM mode

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
