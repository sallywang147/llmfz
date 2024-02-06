#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "target/mips/cpu.h"
#include "target/mips/translate.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct CPUMIPSState env;
  struct DisasContext ctx;

  // Initialize the structures with the fuzzed data
  stream.ConsumeData(&env, sizeof(env));
  stream.ConsumeData(&ctx, sizeof(ctx));

  // Call the function under test
  decode_micromips_opc(&env, &ctx);

  return 0;
}