#include <lcms2.h>
#include <stdint.h>

struct _cmsPipeline_struct73 *
_cmsDefaultICCintents(struct _cmsContext_struct *ContextID, int nProfiles,
                      int *TheIntents, char **hProfiles, int *BPC,
                      double *AdaptationStates, int dwFlags) {
  return cmsDefaultICCintents(ContextID, nProfiles, TheIntents, hProfiles, BPC,
                             AdaptationStates, dwFlags);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 12) {
    return 0;
  }

  int nProfiles = *((const int *)data + 0);
  int dwFlags = *((const int *)data + 1);
  data += 8;
  size -= 8;

  int *TheIntents = new int[nProfiles];
  char **hProfiles = new char *[nProfiles];
  int *BPC = new int[nProfiles];
  double *AdaptationStates = new double[nProfiles];

  for (int i = 0; i < nProfiles; i++) {
    TheIntents[i] = *((const int *)data + 0);
    data += 4;
    size -= 4;

    hProfiles[i] = (char *)data;
    data += 4;
    size -= 4;

    BPC[i] = *((const int *)data + 0);
    data += 4;
    size -= 4;

    AdaptationStates[i] = *((const double *)data + 0);
    data += 8;
    size -= 8;
  }

  struct _cmsContext_struct *ContextID = cmsCreateContext(NULL, NULL);
  struct _cmsPipeline_struct73 *Pipeline =
      _cmsDefaultICCintents(ContextID, nProfiles, TheIntents, hProfiles, BPC,
                            AdaptationStates, dwFlags);
  cmsDeleteContext(ContextID);

  delete[] TheIntents;
  delete[] hProfiles;
  delete[] BPC;
  delete[] AdaptationStates;

  return 0;
}