find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(BufferTest buffer_tests.cpp ${USER_SRC})

target_include_directories(BufferTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(BufferTest GTest::gtest GTest::gtest_main pthread)

gtest_discover_tests(BufferTest)