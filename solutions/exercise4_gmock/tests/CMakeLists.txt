find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_compile_options(--coverage)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
add_compile_options(-fprofile-abs-path)
endif()
add_link_options("--coverage")

add_executable(TemperatureTest 
  test_temperature_sensor.cpp
  ds1820_stub.cpp
  ${USER_SRC}
)

target_include_directories(TemperatureTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(TemperatureTest GTest::gtest GTest::gtest_main gmock)

# gtest_add_tests(TARGET TemperatureTest test_temperature_sensor.cpp)
gtest_discover_tests(TemperatureTest)

