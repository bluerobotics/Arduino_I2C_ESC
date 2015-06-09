/* Blue Robotics Example Code
-------------------------------
 
Title: BlueESC Control via I2C (Arduino)

Description: This example code demonstrates the I2C communication capability
of the Blue Robotics "BlueESC". Motor speed commands are sent via I2C and 
voltage, current, rpm, and temperature data is returned.

The code is designed for the Arduino Uno board and can be compiled and 
uploaded via the Arduino 1.0+ software.

-------------------------------
The MIT License (MIT)

Copyright (c) 2015 Blue Robotics Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-------------------------------*/

#include "Arduino_I2C_ESC.h"

#define ESC_ADDRESS 0x29

Arduino_I2C_ESC motor(ESC_ADDRESS);

float voltage, current, temperature;
int RPM;

void setup() {
  Serial.begin(57600);
  Serial.println("Starting");

  Arduino_I2C_ESC::init();
}

void loop() {
  int signal;

  if ( Serial.available() > 0 ) {
    signal = Serial.parseInt();
    motor.set(signal);
  }

  motor.update();

  Serial.print("ESC: ");
  Serial.print(motor.rpm());Serial.print("RPM\t");
  Serial.print(motor.voltage());Serial.print("V\t");
  Serial.print(motor.current());Serial.print("A\t");
  Serial.print(motor.temperature());Serial.print("`C\t");
  Serial.println();

  delay(250); // Update at roughly 4 hz for the demo

}
