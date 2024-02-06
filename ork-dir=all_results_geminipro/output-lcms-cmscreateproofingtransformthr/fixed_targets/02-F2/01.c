#include "lcms2.h"
#include <stdint.h>

extern "C" {
char * cmsCreateProofingTransformTHR(struct _cmsContext_struct * ContextID, char * InputProfile, int InputFormat, char * OutputProfile, int OutputFormat, char * ProofingProfile, int nIntent, int ProofingIntent, int dwFlags);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 12) {
    return 0;
  }

  uint32_t flags = *((const uint32_t *)data + 0);
  uint32_t intent = *((const uint32_t *)data + 1) % 16;
  int decider = *((int *)data + 2) % 11;
  data += 12;
  size -= 12;

  // Transform using various output formats.
  char *InputProfile = NULL;
  char *OutputProfile = NULL;
  char *ProofingProfile = NULL;

  if (decider == 0) {
    InputProfile = cmsCreate_sRGBProfile();
  } else if (decider == 1) {
    InputProfile = cmsCreateLab4Profile(NULL);
  } else if (decider == 2) {
    InputProfile = cmsCreateXYZProfile();
  } else if (decider == 3) {
    InputProfile = cmsCreateGrayProfile(NULL, NULL);
  } else if (decider == 4) {
    InputProfile = cmsCreateBCHSWabstractProfile(17, 0, 1.2, 0, 3, 5000, 5000);
  } else if (decider == 5) {
    InputProfile = cmsCreateNULLProfile();
  } else if (decider == 6) {
    InputProfile = cmsCreate_OkLabProfile(NULL);
  } else if (decider == 7) {
    OutputProfile = cmsCreate_sRGBProfile();
  } else if (decider == 8) {
    OutputProfile = cmsCreateLab4Profile(NULL);
  } else if (decider == 9) {
    OutputProfile = cmsCreateXYZProfile();
  } else if (decider == 10) {
    OutputProfile = cmsCreateGrayProfile(NULL, NULL);
  }

  if (InputProfile == NULL || OutputProfile == NULL) {
    return 0;
  }

  cmsCreateProofingTransformTHR(NULL, InputProfile, TYPE_RGB_8, OutputProfile, TYPE_RGB_8, ProofingProfile, intent, intent, flags);

  cmsFreeProfile(InputProfile);
  cmsFreeProfile(OutputProfile);

  return 0;
}