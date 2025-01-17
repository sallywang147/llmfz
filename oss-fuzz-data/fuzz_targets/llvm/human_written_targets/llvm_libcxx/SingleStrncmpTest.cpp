// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Simple test for a fuzzer. The fuzzer must find a particular string.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  const char *S = (const char *)Data;
  volatile auto Strncmp = &(strncmp); // Make sure strncmp is not inlined.
  if (Size >= 6 && !Strncmp(S, "qwerty", 6)) {
    fprintf(stderr, "BINGO\n");
    exit(1);
  }
  return 0;
}
