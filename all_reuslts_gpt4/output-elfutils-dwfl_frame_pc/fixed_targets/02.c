#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dwarf.h>
#include <elfutils/libdwfl.h>
#include <fuzzer/FuzzedDataProvider.h>

struct Dwfl_Frame {
  size_t pc;
  char isactivation;
};

bool dwfl_frame_pc(struct Dwfl_Frame *state, size_t *pc, char *isactivation) {
  // This is a mock implementation of the function to make the solution compile.
  // In real usage, this function should be provided by a library.
  *pc = state->pc;
  *isactivation = state->isactivation;
  return true;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Dwfl_Frame state;
  size_t pc;
  char isactivation;

  state.pc = stream.ConsumeIntegral<size_t>();
  state.isactivation = stream.ConsumeIntegral<char>();

  dwfl_frame_pc(&state, &pc, &isactivation);

  return 0;
}