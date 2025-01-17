#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "impeg2_jobq.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct jobq_t ps_jobq;

  // Consume data for the jobq_t structure
  ps_jobq.u4_num_jobs = stream.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_jobq_size = stream.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_jobq_head = stream.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_jobq_tail = stream.ConsumeIntegral<unsigned int>();
  ps_jobq.u4_jobq_buf_len = stream.ConsumeIntegral<unsigned int>();

  // Consume data for the jobq_t structure's pointer members
  size_t jobq_buf_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> jobq_buf = stream.ConsumeBytes<uint8_t>(jobq_buf_size);
  ps_jobq.pv_jobq_buf = jobq_buf.data();

  size_t jobq_mutex_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<uint8_t> jobq_mutex = stream.ConsumeBytes<uint8_t>(jobq_mutex_size);
  ps_jobq.pv_mutex = jobq_mutex.data();

  // Call the target function
  int result = impeg2_jobq_free(&ps_jobq);

  return 0;
}