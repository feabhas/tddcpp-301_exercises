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
#include "Sensor_Adaptor.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD(int, display, (const char* str));
};

class Integration_tests : public ::testing::Test {
protected:
  Integration_tests()          = default;
  virtual ~Integration_tests() = default;

  // Adaptor to test the original stub object
  Sensor::Sensor_Adaptor sensor{};
  // Create our mock object(s)
  StrictMock<mock_display> display{};

  using TS = Temperature_sensor<Sensor::Sensor_Adaptor>;
  TS test_obj{ display, sensor };
};

TEST_F(Integration_tests, test_initialisation)
{
  EXPECT_CALL(display, display(_)).Times(2);

  auto status = test_obj.initialize();
  ASSERT_EQ(status, TS::status::ok);
}

TEST_F(Integration_tests, test_init_display_1st_failure)
{
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, TS::status::display_failure);
}

TEST_F(Integration_tests, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, TS::status::display_failure);
}

TEST_F(Integration_tests, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).Times(3).WillRepeatedly(Return(0));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, TS::status::ok);
}

TEST_F(Integration_tests, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display, display(_)).WillOnce(Return(-1));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, TS::status::display_failure);
}

TEST_F(Integration_tests, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display, display(StartsWith("Family code: 0x")))
    .WillOnce(Return(0));
  EXPECT_CALL(display, display(StartsWith("Serial Number:")))
    .WillOnce(Return(0));
  EXPECT_CALL(display, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, TS::status::ok);
}
