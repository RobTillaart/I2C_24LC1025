
[![Arduino CI](https://github.com/RobTillaart/I2C_24LC1025/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_24LC1025/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_24LC1025.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_24LC1025/releases)


# I2C_24FC1025 - I2C 1MB EEPROM

Arduino library for 24LC1025 and compatible.


## Description

This library is to access external I2C EEPROM of 128 KB in size, 
typically the 24LC1025 and compatible.

Internally it seems to have two I2C addresses? TODO verify.

**Warning**
A2 = Non-Configurable Chip Select.
This pin must be connected to VCC (+5V). 
The device will **NOT** work when this pin floats or is connected to GND (0V).


## Interface

The interface is kept quite identical to the I2C_EEPROM library.


### Constructor

- **I2C_24LC1025(deviceAddress, TwoWire \*wire = &Wire)** constructor.
- **bool begin(pageSize = I2C_24LC1025_PAGESIZE)** initializes the I2C bus and checks if the device is available on the I2C bus.
- **bool begin(sda, scl, pageSize = I2C_24LC1025_PAGESIZE)** idem for ESP32 / ESP8266 and alike.
- **bool isConnected()** test to see if device is on the bus.


### Core functions

- **int writeByte(memoryAddress, value)** write a single byte to the specified memory address.
- **int writeBlock(memoryAddress, buffer, length)** write a buffer starting at the specified memory address. 
- **int setBlock(memoryAddress, value, length)** writes the same byte to length places starting at the specified memory address. Returns 0 if OK.
- **uint8_t readByte(memoryAddress)** read a single byte from a given address
- **uint16_t readBlock(memoryAddress, buffer, length)** read length bytes into buffer starting at specified memory address. Returns the number of bytes read, which should be length.
- **int updateByte(memoryAddress, value)** write a single byte, but only if changed. Returns 0 if value was same or write succeeded.


## Limitation

The library does not offer multiple EEPROMS as one continuous storage device.
(need 2 device address pins for that)


## Future

- See also I2C EEPROM

## Operation

See examples

