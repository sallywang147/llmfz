#include <fftw3.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(struct problem_rdft) + sizeof(struct planner_s) + sizeof(struct P_s)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;

  stream.ConsumeData(&p, sizeof(struct problem_rdft));
  stream.ConsumeData(&plnr, sizeof(struct planner_s));
  stream.ConsumeData(&ego, sizeof(struct P_s));

  mkcldrn_cut(&p, &plnr, &ego);

  return 0;
}