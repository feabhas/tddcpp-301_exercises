// temperature_sensor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "temperature_sensor.h"

#include "ds1820.h"
#include "IDisplay.h"
using namespace Sensor;
using namespace Display;

#include <cstdio>
#include <cstring>

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Temperature_sensor::Temperature_sensor(IDisplay& IDisplay_, Ds1820& sensor_) :
  display{ &IDisplay_ }, sensor{ &sensor_ }
{
}

// a.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit resolution
// b.  Read ROM
// c.  assert ROM CRC value
// d.  On a IDisplay display print out ROM's Family Code and Serial number values
Temperature_sensor::status Temperature_sensor::initialize()
{
  const ROM_t   rom_data = sensor->read_rom();
  const uint8_t crc =
    sensor->calculate_CRC(reinterpret_cast<const uint8_t*>(&rom_data), 7);

  // A stub does not test for error conditions
  // Error if: rom_data.rom_code.crc != crc
  // Error: if rom_data.rom_code.family_code != 0x28


  stringstream family_code{}; // dynamic buffer
  family_code << "Family code: 0x" << hex
              << static_cast<uint32_t>(rom_data.rom_code.family_code) << ends;

  int count = display->display(family_code.str().c_str());
  // Error: if count == -1

  stringstream serial_number{}; // dynamic buffer
  serial_number << "Serial Number: ";
  serial_number << hex;
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[5]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[4]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[3]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[2]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[1]);
  serial_number << ":";
  serial_number << setfill('0') << setw(2)
                << static_cast<uint32_t>(rom_data.rom_code.serial_number[0]);
  serial_number << ends;

  count = display->display(serial_number.str().c_str());
  // Error: if count == -1

  return status::ok;
}

// a.  Instruct the DS18B20 to do a conversion
// b.  Read the Scratchpad
// c.  assert Scratchpad data CRC
// d.  Convert 16-bit raw temperature to floating point degree C
// e.  Convert float to C-string format <nn.nnC>
// f.  Call display display to print C-string value
Temperature_sensor::status Temperature_sensor::run()
{
  sensor->do_conversion();
  scratchpad_data_t scratchpad{};

  const bool okay = sensor->read_scratchpad(&scratchpad);
  // Error: if not okay

  const uint8_t crc = sensor->calculate_CRC(
    reinterpret_cast<const uint8_t*>(&scratchpad), sizeof(scratchpad) - 1);

  // if (scratchpad.crc != crc) {
  //   return status::sensor_failure;
  // }

  const uint16_t raw_sensor_temp = static_cast<uint16_t>(((scratchpad.msb << 8) | scratchpad.lsb));

  const float deg_C = sensor->convert(raw_sensor_temp);
  // Error: if (deg_C < -55.0f) or (deg_C > 125.0f)

  char buff[20] = {};
  sprintf(buff, "%02.2fC", deg_C);

  const int count = display->display(buff);
  // Error: if count == -1

  return status::ok;
}
