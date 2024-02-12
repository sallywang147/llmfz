#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
#include "tpm2_create.h"
#include "tpm2_tool.h"
#include "tpm2_util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct CreateLoaded_In in;
  struct CreateLoaded_Out out;

  in.parent_handle = stream.ConsumeIntegral<uint32_t>();
  in.in_key_handle = stream.ConsumeIntegral<uint32_t>();
  in.out_private_key_handle = stream.ConsumeIntegral<uint32_t>();
  in.out_public_key_handle = stream.ConsumeIntegral<uint32_t>();
  in.name_alg = stream.ConsumeIntegral<uint16_t>();
  in.key_alg = stream.ConsumeIntegral<uint16_t>();
  in.attributes = stream.ConsumeIntegral<uint32_t>();
  in.auth_policy_session = stream.ConsumeIntegral<uint8_t>();
  in.auth_policy_size = stream.ConsumeIntegral<uint16_t>();
  in.auth_policy = stream.ConsumeBytes<uint8_t>(in.auth_policy_size);
  in.auth_key_session = stream.ConsumeIntegral<uint8_t>();
  in.auth_key_size = stream.ConsumeIntegral<uint16_t>();
  in.auth_key = stream.ConsumeBytes<uint8_t>(in.auth_key_size);
  in.auth_parent_session = stream.ConsumeIntegral<uint8_t>();
  in.auth_parent_size = stream.ConsumeIntegral<uint16_t>();
  in.auth_parent = stream.ConsumeBytes<uint8_t>(in.auth_parent_size);
  in.key_bits = stream.ConsumeIntegral<uint16_t>();
  in.key_exponent = stream.ConsumeIntegral<uint32_t>();
  in.template_hash = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<uint16_t>());
  in.parent_key_public = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<uint16_t>());
  in.public_key = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<uint16_t>());
  in.private_key = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegral<uint16_t>());

  TPM2_CreateLoaded(&in, &out);
  return 0;
}