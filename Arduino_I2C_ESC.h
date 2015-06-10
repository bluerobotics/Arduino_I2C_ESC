/* Blue Robotics Arduino I2C ESC Control Library
------------------------------------------------
 
Title: Arduino I2C ESC Library

Description: This library provide methods to control I2C capable ESCs
using the Blue Robotics fork of the tgy firmware. It's designed for the
"BlueESC" but will work with an tgy compatible ESC.

The code is designed for the Arduino boards and can be compiled and 
uploaded via the Arduino 1.0+ software.

Inspired by: https://github.com/balrog-kun/autopilot/blob/lpc1343/actuators-i2c.h

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

#ifndef ARDUINO_I2C_ESC_H
#define ARDUINO_I2C_ESC_H

#include "Arduino.h"

#define MAX_ESCS 16

// THERMISTOR SPECIFICATIONS
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3900
// the value of the 'other' resistor
#define SERIESRESISTOR 3300 

class Arduino_I2C_ESC {
public:
	Arduino_I2C_ESC(uint8_t address, uint8_t poleCount = 6);

	void set(int16_t throttle);

	/* The update function reads new data from the ESC. If used, this function
	 * must be called at least every 65 seconds to prevent 16-bit overflow of 
	 * the timer keeping track of RPM. */
	void update();

	bool isAlive();

	float voltage();

	float current();

	float temperature();

	int16_t rpm();

private:
	uint8_t _address;
	uint16_t _voltage_raw, _current_raw, _temp_raw;
	int16_t _rpm;
	uint16_t _rpmTimer;
	uint8_t _identifier;
	uint8_t _poleCount;

	static void readBuffer(uint8_t address, uint8_t buffer[]);

	void readSensors(uint8_t address, uint16_t *rpm, uint16_t *vbat, uint16_t *temp, uint16_t *curr);
};

#endif
