#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>
#include <xvid.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare the encoder
  struct Encoder enc;
  memset(&enc, 0, sizeof(enc));

  // Prepare the frame
  struct xvid_enc_frame_t xFrame;
  memset(&xFrame, 0, sizeof(xFrame));
  xFrame.version = XVID_VERSION;
  xFrame.bitstream = stream.ConsumeRemainingBytes<uint8_t>().data();
  xFrame.length = stream.remaining_bytes();

  // Prepare the stats
  struct xvid_enc_stats_t stats;
  memset(&stats, 0, sizeof(stats));
  stats.version = XVID_VERSION;

  // Call the function to fuzz
  enc_encode(&enc, &xFrame, &stats);

  return 0;
}