// buffer_tests.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Buffer.h"
#include "gtest/gtest.h"

namespace
{
  class BufferTest : public ::testing::Test {
  protected:
    using TestBuffer = Buffer;

    BufferTest() = default;

    TestBuffer         buffer{};
  };

  TEST_F(BufferTest, defaultConfig)
  {
    ASSERT_EQ(16, buffer.capacity());
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());

    // By enabling the macro ACCESS_CLASS_INTERNALS
    // (defined in testdefs.h) we can examine the
    // private members of our buffer class (by making
    // them public)
    //
    // ASSERT_EQ(0, buffer.read);
    // ASSERT_EQ(0, buffer.write);
  }

  TEST_F(BufferTest, getFromEmpty)
  {
    auto val = buffer.get();
    ASSERT_EQ(std::nullopt, val );
  }

  TEST_F(BufferTest, addSingle)
  {
    auto error = buffer.add(100);
    ASSERT_EQ(1, buffer.size());
    ASSERT_FALSE(buffer.is_empty());
    ASSERT_EQ(TestBuffer::Status::Ok, error);
  }

  TEST_F(BufferTest, getSingle)
  {
    buffer.add(100);
    auto val = buffer.get();

    ASSERT_EQ(100, val);
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
  }

  TEST_F(BufferTest, fillBuffer)
  {
    int capacity = static_cast<int>(buffer.capacity());
    for (int i = 0; i < capacity; ++i) {
      auto error = buffer.add(i);
      ASSERT_EQ(i + 1, buffer.size());
      ASSERT_FALSE(buffer.is_empty());
      ASSERT_EQ(TestBuffer::Status::Ok, error);
    }
  }

  TEST_F(BufferTest, testFlush)
  {
    int capacity = static_cast<int>(buffer.capacity());
    for (int i = 0; i < capacity; ++i) {
      buffer.add(i);
    }
    buffer.flush();
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
  }

  TEST_F(BufferTest, addToFull)
  {
    int capacity = static_cast<int>(buffer.capacity());
    for (int i = 0; i < capacity; ++i) {
      buffer.add(i);
    }

    auto error = buffer.add(100);
    ASSERT_EQ(16, buffer.size());
    ASSERT_FALSE(buffer.is_empty());
    ASSERT_EQ(TestBuffer::Status::Full, error);
  }

  TEST_F(BufferTest, readFromFull)
  {
    for (int i = 0; i < 16; ++i) {
      buffer.add(i);
    }

    int capacity = static_cast<int>(buffer.capacity());
    for (int i = 0; i < capacity; ++i) {
      auto val = buffer.get();
      ASSERT_EQ(i, val);
    }
    ASSERT_EQ(0, buffer.size());
    ASSERT_TRUE(buffer.is_empty());
  }

  TEST_F(BufferTest, readWriteAlternately)
  {
    for (int i = 0; i < 32; ++i) {
      auto status = buffer.add(i);
      ASSERT_EQ(TestBuffer::Status::Ok, status);

      auto val = buffer.get();
      ASSERT_EQ(0, buffer.size());
      ASSERT_EQ(i, val);
      ASSERT_TRUE(buffer.is_empty());
    }
  }
}
