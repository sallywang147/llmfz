#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "impeg2_jobq.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Define and initialize a jobq_t object
  struct jobq_t ps_jobq;

  // Consume data from the fuzzer input
  ps_jobq.i4_jobq_id = provider.ConsumeIntegral<int>();
  ps_jobq.i4_priority = provider.ConsumeIntegral<int>();
  ps_jobq.i4_max_priority = provider.ConsumeIntegral<int>();
  ps_jobq.u4_num_jobs = provider.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_cur_job = provider.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_max_jobs = provider.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_jobq_buf_size = provider.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_job_size = provider.ConsumeIntegral<unsigned int>();

  // Call the function to fuzz
  impeg2_jobq_free(&ps_jobq);

  return 0;
}