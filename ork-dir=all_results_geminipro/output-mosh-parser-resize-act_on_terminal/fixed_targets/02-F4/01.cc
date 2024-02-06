#include <cstddef>
#include <cstdint>

extern "C" {
#include "src/parser/parser.h"
#include "src/terminal/terminal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Terminal::Emulator emulator;
  Parser::Resize resize(emulator);  // Pass the emulator object to the constructor
  for (size_t i = 0; i < size; i++) {
    resize.act(Parser::UserByte(data[i]));  // Remove the &emulator argument
    resize.act_on_terminal(&resize, &emulator);  // Add the call to act_on_terminal
  }

  return 0;
}
```

The fixed code calls the `act_on_terminal` function inside the loop to resolve the issue reported in the error message.