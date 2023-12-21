// test_temperature_sensor_mocks.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;
using ::testing::NaggyMock;
using ::testing::StrictMock;
using ::testing::NaggyMock;
using ::testing::StartsWith;
using ::testing::ContainsRegex;

#include "IDisplay.h"
#include "ISensor.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD(int, display, (const char* str), (override));
};

class mock_sensor : public Sensor::ISensor {
public:
  MOCK_METHOD(std::string, family_code, (), (override));
  MOCK_METHOD(std::string, serial_number, (), (override));
  MOCK_METHOD(float, lastest_reading, (), (override));
};

class full_Mock_tests : public ::testing::Test {
protected:
  full_Mock_tests()          = default;

  // Create our mock object(s)
  StrictMock<mock_display> display_mock{};
  NaggyMock<mock_sensor>  sensor_mock{};

  Temperature_sensor test_obj{ display_mock, sensor_mock };

};

TEST_F(full_Mock_tests, test_initialisation)
{
  EXPECT_CALL(sensor_mock, family_code())
      .WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(sensor_mock, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

  EXPECT_CALL(display_mock, display(_)).Times(2);


  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests, test_init_display_1st_failure)
{
  EXPECT_CALL(sensor_mock, family_code()).WillOnce(Return("Family code: 0x28"));

  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor_mock, family_code()).WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));
  EXPECT_CALL(sensor_mock, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));

  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

    EXPECT_CALL(sensor_mock, family_code())
      .WillOnce(Return("Family code: 0x28"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, lastest_reading())
      .WillOnce(Return(25.0f));

    EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));

    test_obj.initialize();
    auto status = test_obj.run();
    ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(full_Mock_tests, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor_mock, family_code()).WillOnce(Return("Family code: 0x28"));

  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));

  EXPECT_CALL(sensor_mock, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));

  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));

  EXPECT_CALL(sensor_mock, lastest_reading()).WillOnce(Return(25.0f));
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(full_Mock_tests, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(sensor_mock, family_code())
    .WillOnce(Return("Family code: 0x28"));
  EXPECT_CALL(display_mock, display(StartsWith("Family code: 0x")))
    .WillOnce(Return(0));

  EXPECT_CALL(sensor_mock, serial_number())
    .WillOnce(Return("Serial Number:00:00:00:00:00"));
  EXPECT_CALL(display_mock, display(StartsWith("Serial Number:")))
    .WillOnce(Return(0));

  EXPECT_CALL(sensor_mock, lastest_reading())
    .WillOnce(Return(25.0f));
  EXPECT_CALL(display_mock, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}


TEST_F(full_Mock_tests, test_run_incorrect_high_temp)
{
  ::testing::InSequence strict_sequence;

    EXPECT_CALL(sensor_mock, family_code())
      .WillOnce(Return("Family code: 0x28"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, lastest_reading())
      .WillOnce(Return(130.0));

    // EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));

    test_obj.initialize();
    auto status = test_obj.run();
    ASSERT_EQ(status, Temperature_sensor::status::sensor_failure);
}



TEST_F(full_Mock_tests, test_run_incorrect_low_temp)
{
  ::testing::InSequence strict_sequence;

    EXPECT_CALL(sensor_mock, family_code())
      .WillOnce(Return("Family code: 0x28"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, serial_number())
      .WillOnce(Return("Serial Number:00:00:00:00:00"));

    EXPECT_CALL(display_mock, display(_))
      .WillOnce(Return(0));

    EXPECT_CALL(sensor_mock, lastest_reading())
      .WillOnce(Return(-60.0));

    // EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));

    test_obj.initialize();
    auto status = test_obj.run();
    ASSERT_EQ(status, Temperature_sensor::status::sensor_failure);
}
