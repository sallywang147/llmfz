#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tss2_test_fapi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TSS2_TEST_FAPI_CONTEXT test_ctx;
  test_ctx.magic = stream.ConsumeIntegral<uint32_t>();
  test_ctx.version = stream.ConsumeIntegral<uint32_t>();
  test_ctx.esys = reinterpret_cast<ESYS_CONTEXT*>(stream.ConsumeBytes<uint8_t>(sizeof(ESYS_CONTEXT)).data());
  test_ctx.sapi_context = reinterpret_cast<TSS2_SYS_CONTEXT*>(stream.ConsumeBytes<uint8_t>(sizeof(TSS2_SYS_CONTEXT)).data());
  test_ctx.tcti = reinterpret_cast<TSS2_TCTI_CONTEXT*>(stream.ConsumeBytes<uint8_t>(sizeof(TSS2_TCTI_CONTEXT)).data());
  test_ctx.fapi2_tcti = reinterpret_cast<TSS2_TCTI_CONTEXT*>(stream.ConsumeBytes<uint8_t>(sizeof(TSS2_TCTI_CONTEXT)).data());
  test_ctx.config = stream.ConsumeRandomLengthString().c_str();
  test_ctx.log_dir = stream.ConsumeRandomLengthString().c_str();
  test_ctx.keystore_dir = stream.ConsumeRandomLengthString().c_str();
  test_ctx.profile_dir = stream.ConsumeRandomLengthString().c_str();
  test_ctx.profile_name = stream.ConsumeRandomLengthString().c_str();
  test_ctx.user_dir = stream.ConsumeRandomLengthString().c_str();
  test_ctx.system_dir = stream.ConsumeRandomLengthString().c_str();
  test_ctx.tcti_handle = reinterpret_cast<void*>(stream.ConsumeBytes<uint8_t>(sizeof(void*)).data());
  test_ctx.tcti_name = stream.ConsumeRandomLengthString().c_str();
  test_ctx.tcti_config = stream.ConsumeRandomLengthString().c_str();

  // Call the function to fuzz
  test_fapi_checks_pre(&test_ctx);

  return 0;
}