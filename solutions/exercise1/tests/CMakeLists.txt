find_package(GTest REQUIRED)
include(GoogleTest)

add_compile_options(--coverage)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
add_compile_options(-fprofile-abs-path)
endif()

add_link_options("--coverage")

add_executable(BufferTest buffer_tests.cpp ${CMAKE_SOURCE_DIR}/src/Buffer.cpp)

target_include_directories(BufferTest PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

target_link_libraries(BufferTest GTest::gtest_main)

gtest_discover_tests(BufferTest)