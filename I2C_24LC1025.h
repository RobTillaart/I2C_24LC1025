#pragma once
//
//    FILE: I2C_24LC1025.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: I2C_24LC1025 library for Arduino with EEPROM 24LC1025 et al.
// HISTORY: See I2C_24LC1025.cpp
//     URL: https://github.com/RobTillaart/I2C_24LC1025


#include "Arduino.h"
#include "Wire.h"


#define I2C_24LC1025_VERSION        (F("0.2.0"))


#define I2C_DEVICESIZE_24LC1025     131072
#define I2C_PAGESIZE_24LC1025       128


class I2C_24LC1025
{
public:

  I2C_24LC1025(uint8_t deviceAddress, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool      begin(uint8_t sda, uint8_t scl);
#endif
  bool      begin();
  bool      isConnected();


  //  writes a byte to memoryAddress
  //  returns I2C status, 0 = OK
  int       writeByte(const uint32_t memoryAddress, const uint8_t value);
  //  writes length bytes from buffer to EEPROM
  //  returns I2C status, 0 = OK
  int       writeBlock(const uint32_t memoryAddress, const uint8_t *buffer, const uint32_t length);
  //  set length bytes in the EEPROM to the same value.
  //  returns I2C status, 0 = OK
  int       setBlock(const uint32_t memoryAddress, const uint8_t value, const uint32_t length);


  //  returns the value stored in memoryAddress
  uint8_t   readByte(const uint32_t memoryAddress);
  //  reads length bytes into buffer
  //  returns bytes read.
  uint32_t  readBlock(const uint32_t memoryAddress, uint8_t *buffer, const uint32_t length);


  //  updates a byte at memory address, writes only if there is a new value.
  //  return 0 if data is same or written OK, error code otherwise.
  int      updateByte(const uint32_t memoryAddress, const uint8_t value);
  //  updates a block in memory, writes only if there is a new value.
  //  only to be used when you expect to write same buffer multiple times. 
  //  test your performance gains!
  //  returns bytes written.
  uint32_t updateBlock(const uint32_t memoryAddress, const uint8_t* buffer, const uint32_t length);


  //  same functions as above but with verify
  //  return false if write or verify failed.
  bool     writeByteVerify(const uint32_t memoryAddress, const uint8_t value);
  bool     writeBlockVerify(const uint32_t memoryAddress, const uint8_t * buffer, const uint32_t length);
  bool     setBlockVerify(const uint32_t memoryAddress, const uint8_t value, const uint32_t length);
  bool     updateByteVerify(const uint32_t memoryAddress, const uint8_t value);
  bool     updateBlockVerify(const uint32_t memoryAddress, const uint8_t * buffer, const uint32_t length);


  //  Meta data functions
  uint32_t getDeviceSize() { return _deviceSize; };
  uint8_t  getPageSize()   { return _pageSize; };
  uint32_t getLastWrite()  { return _lastWrite; };


private:
  uint8_t  _deviceAddress;
  uint8_t  _actualAddress;   // a.k.a. controlByte
  uint32_t _lastWrite  = 0;
  uint32_t _deviceSize = I2C_DEVICESIZE_24LC1025;
  uint8_t  _pageSize   = I2C_PAGESIZE_24LC1025;
  int      _error      = 0;  // TODO.


  void      _beginTransmission(uint32_t memoryAddress);

  //  returns I2C status, 0 = OK
  int       _pageBlock(uint32_t memoryAddress, const uint8_t* buffer, const uint16_t length, const bool incrBuffer);
  //  returns I2C status, 0 = OK
  int       _WriteBlock(uint32_t memoryAddress, const uint8_t* buffer, const uint8_t length);
  //  returns bytes read.
  int       _ReadBlock(uint32_t memoryAddress, uint8_t* buffer, const uint8_t length);

  TwoWire * _wire;

  bool      _debug = true;
};


// -- END OF FILE --

