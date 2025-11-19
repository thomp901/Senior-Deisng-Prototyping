#ifndef Adafruit_I2CDevice_h
#define Adafruit_I2CDevice_h

// Pico SDK headers for I2C and standard types
#include "hardware/i2c.h" // Needed for i2c_inst_t
#include "pico/types.h"   // Needed for uint32_t, bool, etc.

//#include <Arduino.h>     // Commented out previously
//#include <Wire.h>        // <--- COMMENT THIS OUT!

///< The class which defines how we will talk to this device over I2C
class Adafruit_I2CDevice {
public:
// CHANGE: Replace TwoWire* with i2c_inst_t* (Pico I2C instance)
Adafruit_I2CDevice(uint8_t addr, i2c_inst_t *theWire = i2c0); 
uint8_t address(void);
bool begin(bool addr_detect = true);
void end(void);
bool detected(void);

// These methods will now use i2c_write_blocking/i2c_read_blocking
bool read(uint8_t *buffer, size_t len, bool stop = true);
bool write(const uint8_t *buffer, size_t len, bool stop = true,
const uint8_t *prefix_buffer = nullptr, size_t prefix_len = 0);
bool write_then_read(const uint8_t *write_buffer, size_t write_len,
uint8_t *read_buffer, size_t read_len,
bool stop = false);
bool setSpeed(uint32_t desiredclk); // This might be ignored/unnecessary

size_t maxBufferSize() { return _maxBufferSize; }

private:
uint8_t _addr;
i2c_inst_t *_wire; // CHANGE: Store the Pico I2C instance pointer
bool _begun;
size_t _maxBufferSize;
bool _read(uint8_t *buffer, size_t len, bool stop);
};

#endif // Adafruit_I2CDevice_h
