#include "Arduino_I2C_ESC.h"
#include <Wire.h>

namespace {
  uint8_t _buffer[9];
}

Arduino_I2C_ESC::Arduino_I2C_ESC(uint8_t address, uint8_t poleCount) {
	_address = address;
  _poleCount = poleCount;
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

// Send motor speed command to ESC
void Arduino_I2C_ESC::set(int16_t throttle) {  
  Wire.beginTransmission(_address);
  Wire.write(0x00);
  Wire.write(throttle>>8);
  Wire.write(throttle);  
  Wire.endTransmission();
}

void Arduino_I2C_ESC::update() {  
  _buffer[8] = 0x00; // Reset last byte so we can check for alive

  readBuffer(_address,_buffer);
  
  _rpm = (_buffer[0] << 8) | _buffer[1];
  _voltage_raw = (_buffer[2] << 8) | _buffer[3];
  _temp_raw = (_buffer[4] << 8) | _buffer[5];
  _current_raw = (_buffer[6] << 8) | _buffer[7];
  _identifier = _buffer[8];

  Serial.println(_rpm);

  _rpm = float(_rpm)/((uint16_t(millis())-_rpmTimer)/1000.0f)*60/float(_poleCount);
  _rpmTimer = millis();
}

bool Arduino_I2C_ESC::isAlive() {
  return (_identifier == 0xab);
}

float Arduino_I2C_ESC::voltage() {
	return float(_voltage_raw)/65536.0f*5.0f*6.45f;
}

float Arduino_I2C_ESC::current() {
  return (float(_current_raw)-32767)/65535.0f*5.0f*14.706f;
}

float Arduino_I2C_ESC::temperature() {
  // This code was taken from an Adafruit
	float resistance = SERIESRESISTOR/(65535/float(_temp_raw)-1);

	float steinhart;
	steinhart = resistance / THERMISTORNOMINAL;  // (R/Ro)
	steinhart = log(steinhart);                  // ln(R/Ro)
	steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart;                 // Invert
	steinhart -= 273.15;                         // convert to C

	return steinhart;
}

int16_t Arduino_I2C_ESC::rpm() {
  return _rpm;
}
