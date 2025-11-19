#include "Adafruit_I2CDevice.h"

// --- PICO SDK INCLUDES ---
#include "hardware/i2c.h" 
#include "pico/types.h"
#include "pico/stdlib.h"
#include "pico/time.h"

// Note: For debugging, you can use the printf statements inside the class, 
// which are enabled by defining DEBUG_SERIAL somewhere in your project.

/*!
 * @brief  Create an I2C device at a given address
 * @param  addr The 7-bit I2C address for the device
 * @param  theWire The I2C bus instance to use (i2c0 or i2c1), defaults to i2c0
 */
// NOTE: Must match the constructor in Adafruit_I2CDevice.h:
Adafruit_I2CDevice::Adafruit_I2CDevice(uint8_t addr, i2c_inst_t *theWire) {
  _addr = addr;
  _wire = theWire; // Store the i2c_inst_t pointer
  _begun = false;
  
  // Use a sensible default buffer size for Pico
  _maxBufferSize = 32; 
}

/*!
 * @brief  Initializes and does basic address detection
 * @param  addr_detect Whether we should attempt to detect the I2C address
 * @return True if I2C initialized and a device with the addr found
 */
bool Adafruit_I2CDevice::begin(bool addr_detect) {
  // We assume i2c_init() has been called in main.c to initialize the hardware.
  _begun = true;

  if (addr_detect) {
    return detected();
  }
  return true;
}

/*!
 * @brief  De-initialize device, no-op for Pico SDK (hardware stays initialized)
 */
void Adafruit_I2CDevice::end(void) {
    // No action needed for Pico SDK, as i2c_init is called once in main.c
    _begun = false;
}

/*!
 * @brief  Scans I2C for the address 
 * @return True if I2C initialized and a device with the addr found
 */
bool Adafruit_I2CDevice::detected(void) {
  // Init I2C if not done yet
  if (!_begun && !begin()) {
    return false;
  }

  // Pico SDK: Use a zero-byte write. Success (0 or more bytes written) means ACK.
  int result = i2c_write_blocking(_wire, _addr, nullptr, 0, true);

  if (result >= 0) {
    // Success (device ACKed the address)
    return true;
  }
  // Failed to detect or write
  return false;
}

/*!
 * @brief  Write a buffer or two to the I2C device.
 * @param  buffer Pointer to buffer of data to write.
 * @param  len Number of bytes from buffer to write
 * @param  stop Whether to send an I2C STOP signal on write
 * @param  prefix_buffer Pointer to optional array of data to write before buffer.
 * @param  prefix_len Number of bytes from prefix buffer to write
 * @return True if write was successful, otherwise false.
 */
bool Adafruit_I2CDevice::write(const uint8_t *buffer, size_t len, bool stop,
                               const uint8_t *prefix_buffer, size_t prefix_len) {
  
  if ((len + prefix_len) > maxBufferSize()) {
    return false;
  }

  // 1. Write the prefix data (usually register address)
  if ((prefix_len != 0) && (prefix_buffer != nullptr)) {
    // Write prefix, do NOT send STOP (stop=false)
    int written = i2c_write_blocking(_wire, _addr, prefix_buffer, prefix_len, false);
    if (written != (int)prefix_len) {
      // Failed to write prefix
      return false;
    }
  }

  // 2. Write the main data, using the user's 'stop' flag
  int written = i2c_write_blocking(_wire, _addr, buffer, len, stop);

  if (written == (int)len) {
    return true;
  } else {
    // Failed to write main data
    return false;
  }
}

/*!
 * @brief  Read from I2C into a buffer from the I2C device.
 * @param  buffer Pointer to buffer of data to read into
 * @param  len Number of bytes from buffer to read.
 * @param  stop Whether to send an I2C STOP signal on read
 * @return True if read was successful, otherwise false.
 */
bool Adafruit_I2CDevice::read(uint8_t *buffer, size_t len, bool stop) {
  return _read(buffer, len, stop);
}

bool Adafruit_I2CDevice::_read(uint8_t *buffer, size_t len, bool stop) {
  
  // Pico SDK: Use i2c_read_blocking
  int recv = i2c_read_blocking(_wire, _addr, buffer, len, stop);

  if (recv != (int)len) {
    // Not enough data available or error occurred
    return false;
  }

  // Data is automatically placed into 'buffer' by i2c_read_blocking.
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
 * @param desiredclk The desired I2C SCL frequency
 * @return True
 */
bool Adafruit_I2CDevice::setSpeed(uint32_t desiredclk) {
  (void)desiredclk; // Suppress unused parameter warning
  return true; 
}

// Final definition of the maxBufferSize() function
size_t Adafruit_I2CDevice::maxBufferSize() { return _maxBufferSize; }
