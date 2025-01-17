 #include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "ssh.h"
#include "ssh2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ssh2_userauth_pk_ok(nullptr, nullptr, nullptr, nullptr, stream.ConsumeRemainingBytes());
  return 0;
}