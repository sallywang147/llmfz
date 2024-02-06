#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lcms2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the context
  cmsContext ContextID = cmsCreateContext(NULL, NULL);
  if (ContextID == NULL) {
    return 0;
  }

  // Define the number of profiles
  int nProfiles = stream.ConsumeIntegralInRange<int>(1, 5);

  // Define the intents
  std::vector<int> TheIntents(nProfiles);
  for (int &intent : TheIntents) {
    intent = stream.ConsumeIntegral<int>();
  }

  // Define the profiles
  std::vector<char*> hProfiles(nProfiles);
  for (char* &profile : hProfiles) {
    std::string profile_str = stream.ConsumeRandomLengthString();
    profile = const_cast<char*>(profile_str.c_str());
  }

  // Define the BPC
  std::vector<int> BPC(nProfiles);
  for (int &bpc : BPC) {
    bpc = stream.ConsumeIntegral<int>();
  }

  // Define the AdaptationStates
  std::vector<double> AdaptationStates(nProfiles);
  for (double &state : AdaptationStates) {
    state = stream.ConsumeFloatingPoint<double>();
  }

  // Define the flags
  int dwFlags = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  _cmsDefaultICCintents(ContextID, nProfiles, TheIntents.data(), hProfiles.data(), BPC.data(), AdaptationStates.data(), dwFlags);

  // Cleanup
  cmsDeleteContext(ContextID);

  return 0;
}