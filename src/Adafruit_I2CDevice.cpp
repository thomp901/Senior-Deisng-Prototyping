#include "Adafruit_I2CDevice.h"

// --- PICO SDK INCLUDES ---
#include "hardware/i2c.h" 
#include "pico/types.h"
#include "pico/stdlib.h"
#include "pico/time.h"

/*!
 * @brief  Create an I2C device at a given address
 * @param  addr The 7-bit I2C address for the device
 * @param  theWire The I2C bus instance to use (i2c0 or i2c1), defaults to i2c0
 */
// Constructor updated to use i2c_inst_t*
Adafruit_I2CDevice::Adafruit_I2CDevice(uint8_t addr, i2c_inst_t *theWire) {
  _addr = addr;
  _wire = theWire; // Store the i2c_inst_t pointer
  _begun = false;
  
  _maxBufferSize = 32; 
}

/*!
 * @brief  Initializes and does basic address detection
 * @return True if I2C initialized and a device with the addr found
 */
bool Adafruit_I2CDevice::begin(bool addr_detect) {
  // Assume i2c_init() has been called in main.c
  _begun = true;

  if (addr_detect) {
    return detected();
  }
  return true;
}

/*!
 * @brief  De-initialize device, no-op for Pico SDK
 */
void Adafruit_I2CDevice::end(void) {
    _begun = false;
}

/*!
 * @brief  Scans I2C for the address 
 * @return True if I2C initialized and a device with the addr found
 */
bool Adafruit_I2CDevice::detected(void) {
  if (!_begun && !begin()) {
    return false;
  }

  // Pico SDK: Use a zero-byte write to check for ACK.
  int result = i2c_write_blocking(_wire, _addr, nullptr, 0, true);

  if (result >= 0) {
    return true;
  }
  return false;
}

/*!
 * @brief  Write a buffer or two to the I2C device.
 * @return True if write was successful, otherwise false.
 */
bool Adafruit_I2CDevice::write(const uint8_t *buffer, size_t len, bool stop,
                               const uint8_t *prefix_buffer, size_t prefix_len) {
  
  if ((len + prefix_len) > maxBufferSize()) {
    return false;
  }

  // 1. Write the prefix data (if present) without a STOP
  if ((prefix_len != 0) && (prefix_buffer != nullptr)) {
    int written = i2c_write_blocking(_wire, _addr, prefix_buffer, prefix_len, false);
    if (written != (int)prefix_len) {
      return false;
    }
  }

  // 2. Write the main data, using the user's 'stop' flag
  int written = i2c_write_blocking(_wire, _addr, buffer, len, stop);

  if (written == (int)len) {
    return true;
  } else {
    return false;
  }
}

/*!
 * @brief  Read from I2C into a buffer from the I2C device.
 * @return True if read was successful, otherwise false.
 */
bool Adafruit_I2CDevice::read(uint8_t *buffer, size_t len, bool stop) {
  return _read(buffer, len, stop);
}

// Internal read function using Pico SDK
bool Adafruit_I2CDevice::_read(uint8_t *buffer, size_t len, bool stop) {
  
  int recv = i2c_read_blocking(_wire, _addr, buffer, len, stop);

  if (recv != (int)len) {
    return false;
  }

  return true;
}

/*!
 * @brief  Write some data, then read some data from I2C into another buffer.
 * @return True if write & read was successful, otherwise false.
 */
bool Adafruit_I2CDevice::write_then_read(const uint8_t *write_buffer,
                                         size_t write_len, uint8_t *read_buffer,
                                         size_t read_len, bool stop) {
    if (!write(write_buffer, write_len, stop)) {
        return false;
    }

    return read(read_buffer, read_len);
}

/*!
 * @brief  Returns the 7-bit address of this device
 * @return The 7-bit address of this device
 */
uint8_t Adafruit_I2CDevice::address(void) { return _addr; }

/*!
 * @brief  Change the I2C clock speed. Unused for Pico SDK.
 * @return True
 */
bool Adafruit_I2CDevice::setSpeed(uint32_t desiredclk) {
  (void)desiredclk; 
  return true; 
}

// Final definition of the maxBufferSize() function
size_t Adafruit_I2CDevice::maxBufferSize() { return _maxBufferSize; }