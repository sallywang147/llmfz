 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  problem_rdft p;
  p.n_vars = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.n_clauses = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.n_lits = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.n_vars_alloc = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.n_clauses_alloc = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.n_lits_alloc = stream.ConsumeIntegralInRange<uint32_t>(0, 1000);
  p.clauses = (clause*)malloc(p.n_clauses_alloc * sizeof(clause));
  p.lits = (lit*)malloc(p.n_lits_alloc * sizeof(lit));
  p.vars = (var*)malloc(p.n_vars_alloc * sizeof(var));

  planner_s plnr;
  plnr.ego = (P_s*)malloc(sizeof(P_s));

  mkcldrn_cut(&p, &plnr, plnr.ego);

  free(p.clauses);
  free(p.lits);
  free(p.vars);
  free(plnr.ego);

  return 0;
}