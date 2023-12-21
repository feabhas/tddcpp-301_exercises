// Display_stub.cpp
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

#include "Display_stub.h"
#include <cstring>

namespace Test_stubs
{
  int Display_stub::display([[maybe_unused]] const char* str)
  {
    // Could act as a 'spy' by valdation input parameters, e.g.
    // static unsigned count = 1;
    // switch (count) {
    //   case 1:
    //     CHECK(string{ "Serial Number: 06:05:04:03:02:01" } == string{ str });
    //     break;
    //   case 2:
    //     CHECK(string{ "85.00C" } == string{ str });
    //     break;
    // }
    return static_cast<int>(strlen(str));
  }
} // namespace Display
