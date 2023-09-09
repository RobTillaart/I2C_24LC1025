#pragma once
//
//    FILE: I2C_24LC1025.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.5
// PURPOSE: I2C_24LC1025 library for Arduino with EEPROM 24LC1025 et al.
//     URL: https://github.com/RobTillaart/I2C_24LC1025


#include "Arduino.h"
#include "Wire.h"


#define I2C_24LC1025_VERSION        (F("0.2.5"))


#define I2C_DEVICESIZE_24LC1025     131072
#define I2C_PAGESIZE_24LC1025       128


//  to adjust low level timing (use with care)
//  can also be done on command line.
//  (see private _waitEEReady() function)
#ifndef I2C_WRITEDELAY
#define I2C_WRITEDELAY              5000
#endif


class I2C_24LC1025
{
public:

  I2C_24LC1025(uint8_t deviceAddress, TwoWire *wire = &Wire);


//  MBED test ==> see #55, #53  I2C_EEPROM
#if defined(ESP8266) || defined(ESP32) || (defined(ARDUINO_ARCH_RP2040) && !defined(__MBED__))
  //  set the I2C pins explicitly (overrule)
  bool     begin(uint8_t sda, uint8_t scl, int8_t writeProtectPin = -1);
#endif
  //  use default I2C pins.
  bool     begin(int8_t writeProtectPin = -1);
  bool     isConnected();


  //  writes a byte to memoryAddress
  //  returns I2C status, 0 = OK
  int      writeByte(const uint32_t memoryAddress, const uint8_t value);
  //  writes length bytes from buffer to EEPROM
  //  returns I2C status, 0 = OK
  int      writeBlock(const uint32_t memoryAddress, const uint8_t *buffer, const uint32_t length);
  //  set length bytes in the EEPROM to the same value.
  //  returns I2C status, 0 = OK
  int      setBlock(const uint32_t memoryAddress, const uint8_t value, const uint32_t length);


  //  returns the value stored in memoryAddress
  uint8_t  readByte(const uint32_t memoryAddress);
  //  reads length bytes into buffer
  //  returns bytes read.
  uint32_t readBlock(const uint32_t memoryAddress, uint8_t * buffer, const uint32_t length);


  //  updates a byte at memoryAddress, writes only if there is a new value.
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
  uint32_t getDeviceSize();
  uint8_t  getPageSize();
  uint32_t getLastWrite();


  //  TWR = WriteCycleTime
  //  5 ms is minimum, one can add extra ms here to adjust timing of both read() and write()
  void     setExtraWriteCycleTime(uint8_t ms);
  uint8_t  getExtraWriteCycleTime();


  //  WRITEPROTECT
  //  works only if WP pin is defined in begin().
  //  see readme.md
  inline bool hasWriteProtectPin();
  void     allowWrite();
  void     preventWrite();
  void     setAutoWriteProtect(bool b);
  bool     getAutoWriteProtect();


private:
  uint8_t  _deviceAddress;
  uint8_t  _actualAddress;   //  a.k.a. controlByte
  uint32_t _lastWrite  = 0;  //  for waitEEReady
  uint32_t _deviceSize = I2C_DEVICESIZE_24LC1025;
  uint8_t  _pageSize   = I2C_PAGESIZE_24LC1025;
  uint8_t  _extraTWR = 0;    //  milliseconds
  int      _error    = 0;    //  TODO.


  void     _beginTransmission(uint32_t memoryAddress);

  //  returns I2C status, 0 = OK
  int      _pageBlock(uint32_t memoryAddress, const uint8_t * buffer, const uint16_t length, const bool incrBuffer);
  //  returns I2C status, 0 = OK
  int      _WriteBlock(uint32_t memoryAddress, const uint8_t * buffer, const uint8_t length);
  //  returns bytes read.
  uint8_t  _ReadBlock(uint32_t memoryAddress, uint8_t * buffer, const uint8_t length);

  //  to optimize the write latency of the EEPROM
  void     _waitEEReady();

  TwoWire * _wire;

  bool     _debug = false;

  int8_t   _writeProtectPin = -1;
  bool     _autoWriteProtect = false;
};


//  -- END OF FILE --

