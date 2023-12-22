This is an automatic translation, may be incorrect in some places. See sources and examples!

# Approxy
Linear approximator
- approaches the table to obtain intermediate results
- Work with all types of data
- Progmem mode for storing a table in flash

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** approxy ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/approxy/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


## How it works
Suppose there is a certain * nonlinear * dependence of one value on another, for example, a signal from a sensor
(column x, horizontal axis) and the corresponding physical value (column y, vertical axis):
! [Scheme] (/doc/p1.png)

To get readings from such an unpleasant conditional sensor, you need to know the correspondence between them and the signal from the sensor.
If this compliance is not described by a simple mathematical equation (direct proportionality, Polin, exhibent, logarithm and so on), then
You can calibrate (reinforced) the sensor at several points by building a table.You can do this with a step in a conditional unit,
Having received a large correspondence table for any values.And you can make several points and calculate intermediate values,
Considering the dependence between the linear.This will reduce the size of the table several times without losing it exactly.Example with 11 points (orange line):
! [Scheme] (/doc/p2.png)

This is what this library does.

<a id="init"> </a>
## initialization
### Separate columns (two arrays)
`` `CPP
Approxy <Typex, Typey> Table (Arrayx, Array, Size);
Approxy <Typex, Typey, Ap_pgm> Table (Arrayx, Array, Size);

// Typex and Typey - types of arrays.Can be different
// Arrayx and Array - the arrays themselves
// size - table size (number of lines)
// AP_PGM - Progmem mode
`` `
### General table (two -dimensional array)
`` `CPP
Approxy2d <type>Cranberries Table (Array, Size);
Approxy2d <Type, AP_PGM> Table (Array, Size);

// type - type of array data
// Array - Sammassive
// size - table size (number of lines)
// AP_PGM - Progmem mode
`` `

<a id="usage"> </a>
## Usage
`` `CPP
Float Table.get (Float X);// get an approximated value
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
// Separate table, arrays in RAM
#include <approxy.h>

// table, columns can be of different types
int tx [] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
Float Ty [] = {0, 1, 5, 12, 20, 30, 39, 47, 54, 58, 60};

Approxy <int, float> table (tx, type, 11);

VOID setup () {
  Serial.Begin (9600);

  // Display
  for (int i = 0; i <100; i ++) {
    Serial.println (Table.get (i));
  }
}

VOID loop () {
}
`` `

`` `CPP
// General table in Progmem
#include <approxy.h>

// two -dimensional array, columns have the same type
conste into tab [] [2] progmem = {{
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

Approxy2d <int, ap_pgm> table (Tab, 11);

VOID setup () {
  Serial.Begin (9600);

  // Display
  for (int i = 0; i <100; i ++) {
    Serial.println (Table.get (i));
  }
}

VOID loop () {
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- v1.1 - fixed bug in Approxy2d in RAM mode

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code