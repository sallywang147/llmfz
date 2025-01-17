// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Simple test for a fuzzer. The fuzzer must find the string "Hi!".
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

static volatile int Sink;
static volatile int *Null = 0;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size > 0 && Data[0] == 'H') {
    Sink = 1;
    if (Size > 1 && Data[1] == 'i') {
      Sink = 2;
      if (Size > 2 && Data[2] == '!') {
        printf("Found the target, dereferencing NULL\n");
        *Null = 1;
      }
    }
  }
  return 0;
}
