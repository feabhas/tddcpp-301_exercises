find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(TemperatureTest 
  test_temperature_sensor.cpp
  Display_stub.cpp
  ds1820_stub.cpp
  ${USER_SRC}
)

target_include_directories(TemperatureTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(TemperatureTest GTest::gtest_main)


gtest_discover_tests(TemperatureTest)