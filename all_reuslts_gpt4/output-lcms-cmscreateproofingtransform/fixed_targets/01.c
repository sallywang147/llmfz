#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <lcms2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int InputFormat = stream.ConsumeIntegral<int>();
  int OutputFormat = stream.ConsumeIntegral<int>();
  int nIntent = stream.ConsumeIntegral<int>();
  int ProofingIntent = stream.ConsumeIntegral<int>();
  int dwFlags = stream.ConsumeIntegral<int>();

  // Extract strings
  std::string InputProfile = stream.ConsumeRandomLengthString();
  std::string OutputProfile = stream.ConsumeRandomLengthString();
  std::string ProofingProfile = stream.ConsumeRandomLengthString();

  // Call the function to fuzz
  char *transform = cmsCreateProofingTransform(const_cast<char*>(InputProfile.c_str()), InputFormat, const_cast<char*>(OutputProfile.c_str()), OutputFormat, const_cast<char*>(ProofingProfile.c_str()), nIntent, ProofingIntent, dwFlags);

  // Clean up
  if (transform != nullptr) {
    cmsDeleteTransform(transform);
  }

  return 0;
}