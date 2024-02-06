#include <cstdint>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <xvid.h>
#include <fuzzer/FuzzedDataProvider.h>

xvid_enc_frame_t xFrame;
xvid_enc_stats_t stats;

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  memset(&xFrame, 0, sizeof(xFrame));
  xFrame.version = XVID_VERSION;

  memset(&stats, 0, sizeof(stats));
  stats.version = XVID_VERSION;

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  int int_arg_in_range = stream.ConsumeIntegralInRange(-100, 100);

  // Extract floating point values
  float probability = stream.ConsumeProbability();
  double double_arg = stream.ConsumeFloatingPoint<double>();
  double double_arg_in_range = stream.ConsumeFloatingPointInRange(-1.0, 1.0);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  void *data_ptr = bytes.data();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *ptr = str.c_str();

  // Extract to user defined object
  struct Encoder enc;
  size_t consumed = stream.ConsumeData(&enc, sizeof(enc));

  // Call the function to fuzz
  enc_encode(&enc, &xFrame, &stats);

  return 0;
}