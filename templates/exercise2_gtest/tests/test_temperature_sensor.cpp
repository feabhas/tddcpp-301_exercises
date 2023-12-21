// test_temperature_sensor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "ds1820.h"

#include "Display_stub.h"
#include "gtest/gtest.h"

#include "temperature_sensor.h"

TEST(Stub_tests, test_initialisation)
{
  Sensor::Ds1820 sensor{};
  Test_stubs::Display_stub   display{};

  Temperature_sensor test_obj{ display, sensor };

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

// TEST(Stub_tests, test_basic_algorithm)
// {
//   Sensor::Ds1820 sensor{};
//   Test_stubs::Display_stub   display{};

//   Temperature_sensor test_obj{ display, sensor };

//   test_obj.initialize();
//   auto status = test_obj.run();
//   ASSERT_EQ(status, Temperature_sensor::status::ok);
// }
