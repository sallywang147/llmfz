#include <fuzzer/FuzzedDataProvider.h>

#include <stdlib.h>
#include <string.h>

#include "IndexSharedData.h"
#include "IndexPrivateData.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct IndexSharedData shared_data;
  shared_data.search_type = stream.ConsumeIntegralInRange<int>(0, 1);
  shared_data.search_data = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  shared_data.search_data_len = shared_data.search_data.size();

  struct IndexPrivateData private_data;
  private_data.current_alias = stream.ConsumeIntegralInRange<int>(0, 1);
  private_data.current_alias_len = stream.ConsumeIntegralInRange<int>(0, 1024);

  op_alias_dialog(&shared_data, &private_data, stream.ConsumeIntegralInRange<int>(0, 1));

  return 0;
}