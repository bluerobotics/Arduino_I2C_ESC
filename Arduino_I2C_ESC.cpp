#include "Arduino_I2C_ESC.h"
#include <Wire.h>

Arduino_I2C_ESC::Arduino_I2C_ESC(uint8_t address) {
	_address = address;
}

// Read the incoming data buffer from an ESC
void Arduino_I2C_ESC::readBuffer(uint8_t address, uint8_t buffer[]) {
  Wire.beginTransmission(address);
  Wire.write(0x02); // Data start register
  Wire.endTransmission();
    
  Wire.requestFrom(address,uint8_t(9));
  uint8_t i = 0;
  while(Wire.available()) {
    buffer[i] = Wire.read();
    i++;
  }
}

// Check to make sure that ESC is properly attached
void Arduino_I2C_ESC::init() {
  
}

// Send motor speed command to ESC
void Arduino_I2C_ESC::set(int16_t throttle) {  
  Wire.beginTransmission(_address);
  Wire.write(0x00);
  Wire.write(throttle>>8);
  Wire.write(throttle);  
  Wire.endTransmission();
}

void Arduino_I2C_ESC::update() {  
  readBuffer(_address,buffer);
  
  _rpm_raw = (buffer[0] << 8) | buffer[1];
  _voltage_raw = (buffer[2] << 8) | buffer[3];
  _temp_raw = (buffer[4] << 8) | buffer[5];
  _current_raw = (buffer[6] << 8) | buffer[7];
}

float Arduino_I2C_ESC::voltage() {
	return float(_voltage_raw)/65536*5*6.45;
}

float Arduino_I2C_ESC::current() {
  return (float(_current_raw)-32767)/65535.0f*5*14.706;
}

float Arduino_I2C_ESC::temperature() {
	float resistance = SERIESRESISTOR/(65535/float(_temp_raw)-1);

	float steinhart;
	steinhart = resistance / THERMISTORNOMINAL;     // (R/Ro)
	steinhart = log(steinhart);                  // ln(R/Ro)
	steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart;                 // Invert
	steinhart -= 273.15;                         // convert to C

	return steinhart;
}

int16_t Arduino_I2C_ESC::rpm() {
  return _rpm_raw;
}
