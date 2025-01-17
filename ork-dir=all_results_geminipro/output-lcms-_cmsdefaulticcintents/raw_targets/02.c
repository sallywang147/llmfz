#include <lcms2.h>
#include <stdint.h>

struct _cmsPipeline_struct73 *
_cmsDefaultICCintents(struct _cmsContext_struct *ContextID, int nProfiles, int *TheIntents,
                      char **hProfiles, int *BPC, double *AdaptationStates, int dwFlags) {
  return cmsDefaultICCintents(ContextID, nProfiles, TheIntents, hProfiles, BPC, AdaptationStates,
                             dwFlags);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 16) {
    return 0;
  }

  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  int nProfiles = *((const int *)data + 0);
  int *TheIntents = (int *)data + 1;
  char **hProfiles = (char **)data + 2;
  int *BPC = (int *)data + 3;
  double *AdaptationStates = (double *)data + 4;
  int dwFlags = *((const int *)data + 5);

  struct _cmsPipeline_struct73 *result =
      _cmsDefaultICCintents(ContextID, nProfiles, TheIntents, hProfiles, BPC, AdaptationStates,
                            dwFlags);
  cmsDeleteTransform(result);
  cmsDeleteContext(ContextID);

  return 0;
}