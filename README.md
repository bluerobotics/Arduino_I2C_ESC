# Arduino_I2C_ESC
I2C controlled Arduino library designed for Blue Robotics' BlueESC and other tgy compatible ESCs

# Documentation

Please see the examples for normal operation. Below are the available functions used in the library.

``` cpp
	/* Constructor for ESC instance. Requires input of I2C address (ESC 0,1...16 is address
	 * 0x29,0x2A...0x39). Optionally accepts pole count for RPM measurements. T100 is 6 and 
	 * T200 is 7. */
	Arduino_I2C_ESC(uint8_t address, uint8_t poleCount = 6);

	/* Sends updated throttle setting for the motor. */
	void set(int16_t throttle);

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

# Versions

0.1 - Revision 1 of Arduino_I2C_ESC
