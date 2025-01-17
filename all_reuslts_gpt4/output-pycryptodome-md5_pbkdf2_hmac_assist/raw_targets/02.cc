#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

struct t_hash_state {
  char state[64];
};

extern "C" int MD5_pbkdf2_hmac_assist(struct t_hash_state * inner, struct t_hash_state * outer, char * first_hmac, char * result, size_t iterations);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;
  char first_hmac[64];
  char result[64];
  size_t iterations;

  // Consume data for the inner and outer hash states
  size_t consumed = stream.ConsumeData(&inner, sizeof(inner));
  if (consumed != sizeof(inner)) {
    return 0;
  }
  consumed = stream.ConsumeData(&outer, sizeof(outer));
  if (consumed != sizeof(outer)) {
    return 0;
  }

  // Consume data for the first_hmac
  std::string first_hmac_data = stream.ConsumeBytesAsString(sizeof(first_hmac));
  if (first_hmac_data.size() != sizeof(first_hmac)) {
    return 0;
  }
  std::copy(first_hmac_data.begin(), first_hmac_data.end(), first_hmac);

  // Consume data for iterations
  iterations = stream.ConsumeIntegral<size_t>();

  // Call the target function
  MD5_pbkdf2_hmac_assist(&inner, &outer, first_hmac, result, iterations);

  return 0;
}