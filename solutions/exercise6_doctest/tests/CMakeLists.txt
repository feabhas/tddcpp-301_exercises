
add_compile_options(--coverage)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
add_compile_options(-fprofile-abs-path)
endif()
add_link_options("--coverage")

add_executable(gdo_test test_main.cpp test_gdo.cpp ${USER_SRC})

target_include_directories(gdo_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
  ${CMAKE_SOURCE_DIR}/doctest/doctest
 )

add_test(gdo_test gdo_test)
# include( ${CMAKE_SOURCE_DIR}/doctest/scripts/cmake/doctest.cmake )
# doctest_discover_tests(gdo_test)