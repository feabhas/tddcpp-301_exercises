// Display_stub.h
// See project README.md for disclaimer and additional information.
// Feabhas Ltd

/** @file Display_stub.h
    \brief API for the abstracted Display Interface.
*/
#ifndef _DISPLAY_STUB_H
#define _DISPLAY_STUB_H

#include "IDisplay.h"

namespace Test_stubs
{
  class Display_stub : public Display::IDisplay {
  public:
    Display_stub()  = default;
    ~Display_stub() = default;
    int display(const char* str) override;
  };

} // namespace

#endif // _DISPLAY_STUB_H_
