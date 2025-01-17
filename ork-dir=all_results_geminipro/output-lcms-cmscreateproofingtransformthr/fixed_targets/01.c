#include "lcms2.h"
#include <stdint.h>

extern "C" {
#include <lcms2_plugin.h>
}

char * cmsCreateProofingTransformTHR(struct _cmsContext_struct * ContextID, char * InputProfile, int InputFormat, char * OutputProfile, int OutputFormat, char * ProofingProfile, int nIntent, int ProofingIntent, int dwFlags) {
  cmsHPROFILE hInputProfile = cmsOpenProfileFromMem(InputProfile, strlen(InputProfile));
  cmsHPROFILE hOutputProfile = cmsOpenProfileFromMem(OutputProfile, strlen(OutputProfile));
  cmsHPROFILE hProofingProfile = cmsOpenProfileFromMem(ProofingProfile, strlen(ProofingProfile));

  if (!hInputProfile || !hOutputProfile || !hProofingProfile) {
    cmsCloseProfile(hInputProfile);
    cmsCloseProfile(hOutputProfile);
    cmsCloseProfile(hProofingProfile);
    return NULL;
  }

  char *result = cmsCreateProofingTransformTHR(ContextID, hInputProfile, InputFormat, hOutputProfile, OutputFormat, hProofingProfile, nIntent, ProofingIntent, dwFlags);

  cmsCloseProfile(hInputProfile);
  cmsCloseProfile(hOutputProfile);
  cmsCloseProfile(hProofingProfile);

  return result;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 12) {
    return 0;
  }

  cmsContext ContextID = cmsCreateContext(NULL, NULL);

  uint32_t flags = *((const uint32_t *)data + 0);
  uint32_t intent = *((const uint32_t *)data + 1) % 16;
  uint32_t proofing_intent = *((const uint32_t *)data + 2) % 16;
  int decider = *((int *)data + 3) % 11;
  data += 16;
  size -= 16;

  // Transform using various output formats.
  char *InputProfile = (char *)data;
  data += strlen(InputProfile) + 1;
  size -= strlen(InputProfile) + 1;

  char *OutputProfile = (char *)data;
  data += strlen(OutputProfile) + 1;
  size -= strlen(OutputProfile) + 1;

  char *ProofingProfile = (char *)data;
  data += strlen(ProofingProfile) + 1;
  size -= strlen(ProofingProfile) + 1;

  cmsCreateProofingTransformTHR(ContextID, InputProfile, decider, OutputProfile, decider, ProofingProfile, intent, proofing_intent, flags);

  cmsDeleteContext(ContextID);

  return 0;
}