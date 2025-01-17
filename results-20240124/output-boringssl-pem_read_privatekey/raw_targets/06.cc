 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string input_string = stream.ConsumeRemainingBytesAsString();
  struct _IO_FILE* file = fmemopen(const_cast<char*>(input_string.c_str()),
                                  input_string.size(), "r");
  if (file == nullptr) {
    return 0;
  }

  struct evp_pkey_st* key = nullptr;
  struct evp_pkey_st** key_ptr = &key;
  PEM_read_PrivateKey(file, key_ptr, nullptr, nullptr);
  fclose(file);
  return 0;
}