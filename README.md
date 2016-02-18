# Arduino_I2C_ESC [![Build Status](https://travis-ci.org/bluerobotics/Arduino_I2C_ESC.svg?branch=master)](https://travis-ci.org/bluerobotics/Arduino_I2C_ESC)

I2C controlled Arduino library designed for Blue Robotics' BlueESC and other tgy compatible ESCs

# Documentation

Please see the examples for normal operation. Below are the available functions used in the library.

``` cpp
	/* Constructor for ESC instance. Requires input of I2C address (ESC 0,1...15 is address
	 * 0x29,0x2A...0x38). Optionally accepts pole count for RPM measurements. T100 is 6 and 
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
```

## How to Set I<sup>2</sup>C Address on Blue Robotics ESC

Please see [instructions here on how to change I<sup>2</sup>C address](http://docs.bluerobotics.com/bluesc/#assigning-isup2supc-addresses).

The default address (ESC 0) is 0x29 (41 in decimal). Each ESC after that (ESC 1, ESC 2, etc) is 0x29 + 1, 2, etc. Here is a full list of addresses for reference:

| ESC # | Hex Address | Decimal Address |
| ---: | :---: | :---: |
| 0 | 0x29 | 41 |
| 1 | 0x2A | 42 |
| 2 | 0x2B | 43 |
| 3 | 0x2C | 44 |
| 4 | 0x2D | 45 |
| 5 | 0x2E | 46 |
| 6 | 0x2F | 47 |
| 7 | 0x30 | 48 |
| 8 | 0x31 | 49 |
| 9 | 0x32 | 50 |
| 10 | 0x33 | 51 |
| 11 | 0x34 | 52 |
| 12 | 0x35 | 53 |
| 13 | 0x36 | 54 |
| 14 | 0x37 | 55 |
| 15 | 0x38 | 56 |

# Versions

0.0.1 - Revision 1 of Arduino_I2C_ESC
1.0.0 - First official release of Arduino Library
