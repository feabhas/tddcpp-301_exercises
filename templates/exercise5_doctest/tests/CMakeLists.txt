
add_executable(gdo_test test_main.cpp test_gdo.cpp ${USER_SRC})

target_include_directories(gdo_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/inc
 )

add_test(gdo_test gdo_test)

target_include_directories(gdo_test PUBLIC ${DOCTEST_INCLUDE_DIR})

# include( ${CMAKE_SOURCE_DIR}/doctest/scripts/cmake/doctest.cmake )
# doctest_discover_tests(gdo_test)