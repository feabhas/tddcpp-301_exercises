// buffer_tests.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Buffer.h"
#include <gtest/gtest.h>

TEST(setup_test_case, testWillPass)
{
    ASSERT_EQ(42, 42);
}

TEST(setup_test_case, testWillFail)
{
    ASSERT_EQ(42, 0);
}
