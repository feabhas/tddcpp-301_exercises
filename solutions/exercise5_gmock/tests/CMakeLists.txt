# find_package(GTest CONFIG REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

add_compile_options(
  --coverage
  -fprofile-abs-path
)
add_link_options("--coverage")


add_executable(TemperatureTestMock 
  test_temperature_sensor_mocks.cpp
  ${USER_SRC}
)

target_include_directories(TemperatureTestMock PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(TemperatureTestMock GTest::gtest_main gmock)

# gtest_add_tests(TARGET TemperatureTestMock test_temperature_sensor.cpp)
gtest_discover_tests(TemperatureTestMock)


add_executable(TemperatureTest 
  test_temperature_sensor.cpp
  ds1820_stub.cpp
  Sensor_adaptor.cpp
  ${USER_SRC}
)

target_include_directories(TemperatureTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(TemperatureTest GTest::gtest_main gmock)

# gtest_add_tests(TARGET TemperatureTest test_temperature_sensor.cpp)
gtest_discover_tests(TemperatureTest)

