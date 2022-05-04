This is an automatic translation, may be incorrect in some places. See sources and examples!

# Approxy
Linear Approximator
- Approximates the table to get intermediate results
- Working with all types of data- PROGMEM mode for table storage in Flash

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **Approxy** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/Approxy/archive/refs/heads/main.zip) .zip archive for manual installation:- Extract and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

## How it works
Suppose there is some *nonlinear* dependence of one value on another, for example, a signal from a sensor
(column X, horizontal axis) and its corresponding physical value (column Y, vertical axis):
![scheme](/docs/p1.png)Cranberry
To get readings from such an unpleasant conditional sensor, you need to know the correspondence between them and the signal from the sensor.
If this correspondence is not described by a simple mathematical equation (direct proportionality, polynomial, exponential, logarithm, and so on), then
you can calibrate (calibrate) the sensor at several points by building a table. You can do this in increments of a conventional unit,
having received a large table of correspondences for any values. And you can make several points and calculate intermediate values,
assuming that the relationship between them is linear. This will reduce the size of the table several times without much loss in accuracy. Example with 11 points (orange line):
![scheme](/docs/p2.png)

This is exactly what this library does.<a id="init"></a>
## Initialization
### Separate columns (two arrays)
```cpp
Approxy<typeX, typeY> table(arrayX, arrayY, size);
Approxy<typeX, typeY, AP_PGM> table(arrayX, arrayY, size);

// typeX and typeY are array data types. May be different
// arrayX and arrayY are arrays themselves
// size - table size (number of rows)// AP_PGM - PROGMEM mode
```
### General table (two-dimensional array)
```cpp
Approxy2D<type> table(array, size);
Approxy2D<type, AP_PGM> table(array, size);

// type - array data type
// array - the array itself
// size - table size (number of rows)// AP_PGM - PROGMEM mode
```

<a id="usage"></a>
## Usage
```cpp
floattable.get(float x); // get approximate value
```

<a id="example"></a>## Example
See **examples** for other examples!
```cpp
// separate table, arrays in RAM
#include <Approxy.h>

// table, columns can be of different types
int tx[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
float ty[] = {0, 1, 5, 12, 20, 30, 39, 47, 54, 58, 60};Approxy<int, float> table(tx, ty, 11);

void setup() {
  Serial.begin(9600);

  // output
  for (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}Cranberry
void loop() {
}
```

```cpp
// general table in PROGMEM
#include <Approxy.h>

// two-dimensional array, columns have the same typeconst int tab[][2] PROGMEM = {
  {0, 0},
  {10, 1},
  {20, 5},
  {30, 12},
  {40, 20},
  {50, 30},
  {60, 39},
  {70, 47},
  {80, 54},{90, 58},
  {100, 60},
};

Approxy2D<int, AP_PGM> table(tab, 11);

void setup() {
  Serial.begin(9600);

  // outputfor (int i = 0; i < 100; i++) {
    Serial.println(table.get(i));
  }
}

void loop() {
}
```

<a id="versions"></a>## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!