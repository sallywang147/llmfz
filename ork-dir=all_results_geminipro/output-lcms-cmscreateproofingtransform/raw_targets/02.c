#include <lcms2.h>
#include <stdint.h>

char * cmsCreateProofingTransform(char * InputProfile, int InputFormat, char * OutputProfile, int OutputFormat, char * ProofingProfile, int nIntent, int ProofingIntent, int dwFlags) {
  cmsHPROFILE hInputProfile = cmsOpenProfileFromMem(InputProfile, strlen(InputProfile));
  cmsHPROFILE hOutputProfile = cmsOpenProfileFromMem(OutputProfile, strlen(OutputProfile));
  cmsHPROFILE hProofingProfile = cmsOpenProfileFromMem(ProofingProfile, strlen(ProofingProfile));

  if (!hInputProfile || !hOutputProfile || !hProofingProfile) {
    if (hInputProfile) cmsCloseProfile(hInputProfile);
    if (hOutputProfile) cmsCloseProfile(hOutputProfile);
    if (hProofingProfile) cmsCloseProfile(hProofingProfile);
    return NULL;
  }

  char *result = (char *)cmsCreateProofingTransformTHR(hInputProfile, InputFormat, hOutputProfile, OutputFormat, hProofingProfile, nIntent, ProofingIntent, dwFlags);

  cmsCloseProfile(hInputProfile);
  cmsCloseProfile(hOutputProfile);
  cmsCloseProfile(hProofingProfile);

  return result;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 64) {
    return 0;
  }

  int InputFormat = *((const uint32_t *)data + 0) % 13;
  int OutputFormat = *((const uint32_t *)data + 1) % 13;
  int nIntent = *((const uint32_t *)data + 2) % 16;
  int ProofingIntent = *((const uint32_t *)data + 3) % 16;
  int dwFlags = *((const uint32_t *)data + 4) % 10;
  data += 20;
  size -= 20;

  char *InputProfile = (char *)data;
  data += 32;
  size -= 32;

  char *OutputProfile = (char *)data;
  data += 32;
  size -= 32;

  char *ProofingProfile = (char *)data;

  char *result = cmsCreateProofingTransform(InputProfile, InputFormat, OutputProfile, OutputFormat, ProofingProfile, nIntent, ProofingIntent, dwFlags);

  if (result) {
    free(result);
  }

  return 0;
}