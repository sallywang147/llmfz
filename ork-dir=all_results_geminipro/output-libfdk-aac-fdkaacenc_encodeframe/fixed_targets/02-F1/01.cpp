#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "fdk-aac/aacenc_lib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int input_buffer_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  short* input_buffer = new short[input_buffer_size];
  stream.ConsumeData(input_buffer, input_buffer_size * sizeof(short));

  const int n_out_bytes = stream.ConsumeIntegralInRange<int>(0, 1024);
  int* n_out_bytes_ptr = new int[n_out_bytes];
  stream.ConsumeData(n_out_bytes_ptr, n_out_bytes * sizeof(int));

  const int ext_payload_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  AACENC_EXT_PAYLOAD* ext_payload = new AACENC_EXT_PAYLOAD[ext_payload_size];
  stream.ConsumeData(ext_payload, ext_payload_size * sizeof(AACENC_EXT_PAYLOAD));

  struct AAC_ENC* h_aac_enc = new AAC_ENC;
  struct TRANSPORTENC* h_tp_enc = new TRANSPORTENC;

  FDKaacEnc_EncodeFrame(h_aac_enc, h_tp_enc, input_buffer, input_buffer_size,
                        n_out_bytes_ptr, ext_payload);

  delete[] input_buffer;
  delete[] n_out_bytes_ptr;
  delete[] ext_payload;
  delete h_aac_enc;
  delete h_tp_enc;

  return 0;
}