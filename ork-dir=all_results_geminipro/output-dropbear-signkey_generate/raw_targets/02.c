#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "dss.h"
#include "ed25519.h"
#include "fuzz.h"
#include "session.h"
#include "signkey.h"
#include "ssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int keytype = stream.ConsumeIntegral<int>();
  const int bits = stream.ConsumeIntegral<int>();
  const std::string filename = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 1024));
  const int skip_exist = stream.ConsumeBool();

  signkey_generate(keytype, bits, const_cast<char*>(filename.c_str()), skip_exist);
  return 0;
}