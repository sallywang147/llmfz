#include <fuzzer/FuzzedDataProvider.h>
#include <lcms2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create ContextID
  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  if (ContextID == NULL) {
    return 0;
  }

  // Create InputProfile
  std::vector<unsigned char> InputProfileBytes = stream.ConsumeBytes<unsigned char>(stream.remaining_bytes() / 3);
  cmsHPROFILE InputProfile = cmsOpenProfileFromMem(InputProfileBytes.data(), InputProfileBytes.size());
  if (InputProfile == NULL) {
    cmsDeleteContext(ContextID);
    return 0;
  }

  // Create OutputProfile
  std::vector<unsigned char> OutputProfileBytes = stream.ConsumeBytes<unsigned char>(stream.remaining_bytes() / 2);
  cmsHPROFILE OutputProfile = cmsOpenProfileFromMem(OutputProfileBytes.data(), OutputProfileBytes.size());
  if (OutputProfile == NULL) {
    cmsCloseProfile(InputProfile);
    cmsDeleteContext(ContextID);
    return 0;
  }

  // Create ProofingProfile
  std::vector<unsigned char> ProofingProfileBytes = stream.ConsumeRemainingBytes<unsigned char>();
  cmsHPROFILE ProofingProfile = cmsOpenProfileFromMem(ProofingProfileBytes.data(), ProofingProfileBytes.size());
  if (ProofingProfile == NULL) {
    cmsCloseProfile(OutputProfile);
    cmsCloseProfile(InputProfile);
    cmsDeleteContext(ContextID);
    return 0;
  }

  // Consume int values
  int InputFormat = stream.ConsumeIntegral<int>();
  int OutputFormat = stream.ConsumeIntegral<int>();
  int nIntent = stream.ConsumeIntegral<int>();
  int ProofingIntent = stream.ConsumeIntegral<int>();
  int dwFlags = stream.ConsumeIntegral<int>();

  // Call the target function
  cmsHTRANSFORM transform = cmsCreateProofingTransformTHR(ContextID, InputProfile, InputFormat, OutputProfile, OutputFormat, ProofingProfile, nIntent, ProofingIntent, dwFlags);

  // Cleanup
  if (transform != NULL) {
    cmsDeleteTransform(transform);
  }
  cmsCloseProfile(ProofingProfile);
  cmsCloseProfile(OutputProfile);
  cmsCloseProfile(InputProfile);
  cmsDeleteContext(ContextID);

  return 0;
}