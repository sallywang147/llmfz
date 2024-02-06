#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lcms2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int nProfiles = stream.ConsumeIntegral<int>();
  int dwFlags = stream.ConsumeIntegral<int>();

  // Extract a vector of integers for TheIntents and BPC
  std::vector<int> TheIntents = stream.ConsumeIntegralInRange<int>(0, nProfiles);
  std::vector<int> BPC = stream.ConsumeIntegralInRange<int>(0, nProfiles);

  // Extract a vector of doubles for AdaptationStates
  std::vector<double> AdaptationStates = stream.ConsumeIntegralInRange<double>(0, nProfiles);

  // Extract a vector of strings for hProfiles
  std::vector<std::string> hProfilesStrs(nProfiles);
  char* hProfiles[nProfiles];
  for (int i = 0; i < nProfiles; ++i) {
    hProfilesStrs[i] = stream.ConsumeRandomLengthString();
    hProfiles[i] = const_cast<char*>(hProfilesStrs[i].c_str());
  }

  // Create a context
  cmsContext ContextID = cmsCreateContext(NULL, NULL);

  // Call the target function
  _cmsDefaultICCintents(ContextID, nProfiles, TheIntents.data(), hProfiles, BPC.data(), AdaptationStates.data(), dwFlags);

  // Clean up
  cmsDeleteContext(ContextID);

  return 0;
}