#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" char * verify_signature(struct Bytes * signature, struct RSApub * pk, char * edigest, struct Elem ** psigalg);

struct Bytes {
  size_t size;
  uint8_t *data;
};

struct RSApub {
  int n_len;
  uint8_t *n;
  int e_len;
  uint8_t *e;
};

struct Elem {
  int type;
  void *value;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  
  struct Bytes signature;
  struct RSApub pk;
  struct Elem sigalg;
  
  // Split the input data into segments for different parameters
  size_t signature_size = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<uint8_t> signature_data = stream.ConsumeBytes<uint8_t>(signature_size);
  signature.size = signature_data.size();
  signature.data = signature_data.data();

  size_t n_len = stream.ConsumeIntegralInRange<size_t>(0, size / 4);
  std::vector<uint8_t> n_data = stream.ConsumeBytes<uint8_t>(n_len);
  pk.n_len = n_data.size();
  pk.n = n_data.data();

  size_t e_len = stream.ConsumeIntegralInRange<size_t>(0, size / 4);
  std::vector<uint8_t> e_data = stream.ConsumeBytes<uint8_t>(e_len);
  pk.e_len = e_data.size();
  pk.e = e_data.data();

  // edigest is a null-terminated string
  std::string edigest = stream.ConsumeRemainingBytesAsString();

  struct Elem *psigalg = &sigalg;
  
  verify_signature(&signature, &pk, edigest.data(), &psigalg);
  
  return 0;
}