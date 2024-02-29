// temperature_sensor.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

/** @file temperature_sensor.h
    \brief API for the abstracted Temperature Sensor module.
*/
#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

#include "IDisplay.h"



template <typename Ty> 
class Temperature_sensor {
public:
  enum class status { ok, sensor_failure, display_failure };

  Temperature_sensor(Display::IDisplay &IDisplay_, Ty &sensor_)
      : display{&IDisplay_}, sensor{&sensor_} {}

  /*! \fn void Temperture_sensor::initialize()
  \brief Perform initialization of the sensor and display
  \return whether the initialization was successful.
  */
  auto initialize() -> status {
    int count = display->display(sensor->family_code().c_str());
    if (count == -1) {
      return status::display_failure;
    }

    count = display->display(sensor->serial_number().c_str());

    if (count == -1) {
      // display display error
      return status::display_failure;
    }
    return status::ok;
  }

  /*! \fn void Temperture_sensor::run()
  \brief Perform the reading of the raw temperature sensor and displays the
  value \return whether the reading and conversion of the temperature was
  successful.
    */
  auto run() -> status {
    const float deg_C = sensor->lastest_reading();
    if ((deg_C < -55.0f) || (deg_C > 125.0f)) {
      // Out of range error
      return status::sensor_failure;
    }

    char buff[20] = {};
    sprintf(buff, "%02.2fC", deg_C);

    const int count = display->display(buff);

    if (count == -1) {
      return status::display_failure;
    }
    return status::ok;
  }

private:
  Display::IDisplay *display{};
  Ty *sensor{};
};

#endif // _TEMPERATURE_SENSOR_H
