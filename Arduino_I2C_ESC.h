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
	/* Constructor for ESC instance. Requires input of I2C address (ESC 0,1...16 is address
	 * 0x29,0x2A...0x39). Optionally accepts pole count for RPM measurements. T100 is 6 and 
	 * T200 is 7. */
	Arduino_I2C_ESC(uint8_t address, uint8_t poleCount = 6);

	/* Sends updated throttle setting for the motor. Throttle input range is 16 bit
	 * (-32767 to +32767). */
	void set(int16_t throttle);

	/* Alternate function to set throttle using standard servo pulse range (1100-1900) */
	void setPWM(int16_t pwm);

	/* The update function reads new data from the ESC. If used, this function
	 * must be called at least every 65 seconds to prevent 16-bit overflow of 
	 * the timer keeping track of RPM. Recommended to call this function at 4-10 Hz */
	void update();

	/* Returns true if the ESC is connected */
	bool isAlive();

	/* Returns voltage measured by the ESC in volts */
	float voltage();

	/* Returns current measured by the ESC in amps */
	float current();

	/* Returns temperature measured by the ESC in degree Celsius */
	float temperature();

	/* Returns RPM of the motor. Note that this measurement will be
	 * more accurate if the I2C data is read slowly. */
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
