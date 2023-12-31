// test_temperature_sensor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::StartsWith;
using ::testing::ContainsRegex;

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"


class Mock_tests : public ::testing::Test {
protected:
  Mock_tests()          = default;

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)

};

TEST_F(Mock_tests, test_initialisation)
{
  GTEST_SKIP();
}

TEST_F(Mock_tests, test_init_display_1st_failure)
{
  GTEST_SKIP();
}

TEST_F(Mock_tests, test_init_display_2nd_failure)
{
  GTEST_SKIP();
}

TEST_F(Mock_tests, test_run_display_no_failure)
{
  GTEST_SKIP();
}

TEST_F(Mock_tests, test_init_display_3nd_failure)
{
  GTEST_SKIP();
}

TEST_F(Mock_tests, test_init_display_param_check)
{
  GTEST_SKIP();
}
