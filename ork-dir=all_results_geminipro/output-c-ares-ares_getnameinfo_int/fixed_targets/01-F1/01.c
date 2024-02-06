#include <stddef.h>

extern "C" {
#include "ares.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size);

// Entrypoint for Clang's libfuzzer
int LLVMFuzzer