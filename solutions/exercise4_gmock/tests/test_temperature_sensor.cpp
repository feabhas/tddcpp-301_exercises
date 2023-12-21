// test_temperature_sensor.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;
using ::testing::_;
using ::testing::A;
using ::testing::NiceMock;
using ::testing::NaggyMock;
using ::testing::StrictMock;
using ::testing::StartsWith;
using ::testing::ContainsRegex;

#include "IDisplay.h"
#include "ds1820.h"
#include "temperature_sensor.h"

class mock_display : public Display::IDisplay {
public:
  MOCK_METHOD(int ,display, (const char* str), (override));
};

class Mock_tests : public ::testing::Test {
protected:
  Mock_tests()          = default;
  virtual ~Mock_tests() = default;

  // stub object
  Sensor::Ds1820 sensor{};
  // Create our mock object(s)
  // NiceMock<mock_display> display{};
  // NaggyMock<mock_display> display{};
  StrictMock<mock_display> display_mock{};

  Temperature_sensor test_obj{ display_mock, sensor };

};

TEST_F(Mock_tests, test_initialisation)
{
  EXPECT_CALL(display_mock, display(_)).Times(2);
  // EXPECT_CALL(display_mock, display(A<const char*>())).Times(2).WillRepeatedly(Return(0));
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests, test_init_display_1st_failure)
{
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests, test_init_display_2nd_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));
  auto status = test_obj.initialize();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}

TEST_F(Mock_tests, test_run_display_no_failure)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display_mock, display(_)).Times(1).WillRepeatedly(Return(0));
  // test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}

TEST_F(Mock_tests, test_init_display_3nd_failure)
{
  ::testing::InSequence strict_sequence;

  // EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));
  // EXPECT_CALL(display_mock, display(_)).WillOnce(Return(0));
  EXPECT_CALL(display_mock, display(_)).WillOnce(Return(-1));

  // test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::display_failure);
}



TEST_F(Mock_tests, test_init_display_param_check)
{
  ::testing::InSequence strict_sequence;

  EXPECT_CALL(display_mock, display(StartsWith("Family code: 0x"))).WillOnce(Return(0));
  EXPECT_CALL(display_mock, display(StartsWith("Serial Number:"))).WillOnce(Return(0));
  EXPECT_CALL(display_mock, display(ContainsRegex("..\\...C"))).WillOnce(Return(0));

  test_obj.initialize();
  auto status = test_obj.run();
  ASSERT_EQ(status, Temperature_sensor::status::ok);
}
