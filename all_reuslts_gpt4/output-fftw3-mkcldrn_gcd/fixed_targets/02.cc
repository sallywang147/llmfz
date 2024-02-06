#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function
  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;

  // Consume data for the parameters from the fuzzing input
  if (stream.remaining_bytes() < sizeof(p) + sizeof(plnr) + sizeof(ego)) {
    return 0;
  }

  stream.ConsumeData(&p, sizeof(p));
  stream.ConsumeData(&plnr, sizeof(plnr));
  stream.ConsumeData(&ego, sizeof(ego));

  // Call the function with the initialized parameters
  mkcldrn_gcd(&p, &plnr, &ego);

  return 0;
}