#include <fuzzer/FuzzedDataProvider.h>
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

  // Create a context
  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  if (!ContextID) {
    return 0;
  }

  // Call the target function
  char *result = cmsCreateProofingTransformTHR(ContextID, (char *)InputProfile.c_str(), InputFormat, (char *)OutputProfile.c_str(), OutputFormat, (char *)ProofingProfile.c_str(), nIntent, ProofingIntent, dwFlags);

  // Cleanup
  cmsDeleteTransform(result);
  cmsDeleteContext(ContextID);

  return 0;
}