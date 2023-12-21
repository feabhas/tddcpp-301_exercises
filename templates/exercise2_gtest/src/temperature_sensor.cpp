// temperature_sensor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "temperature_sensor.h"

#include "ds1820.h"
#include "IDisplay.h"


Temperature_sensor::Temperature_sensor(Display::IDisplay& IDisplay_, Sensor::Ds1820& sensor_) :
  display{ &IDisplay_ }, sensor{ &sensor_ }
{
}

// a.  Initialize the DS18B20 to be configurable for 9, 10, 11 or 12-bit resolution
// b.  Read ROM
// c.  assert ROM CRC value
// d.  On a IDisplay display print out ROM's Family Code and Serial number values
Temperature_sensor::status Temperature_sensor::initialize()
{
  // TBD - see CODE.md for hints
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
  // TBD - see CODE.md for hints
  return status::ok;
}
