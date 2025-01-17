#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize IndexSharedData and IndexPrivateData.
  struct IndexSharedData shared_data;
  struct IndexPrivateData private_data;

  // Generate random values for the arguments of op_alias_dialog.
  int arg_3 = provider.ConsumeIntegral<int>();

  // Call op_alias_dialog with the generated arguments.
  int result = op_alias_dialog(&shared_data, &private_data, arg_3);

  // Consume the remaining input.
  std::vector<uint8_t> remaining_input = provider.ConsumeRemainingBytes();

  return result;
}