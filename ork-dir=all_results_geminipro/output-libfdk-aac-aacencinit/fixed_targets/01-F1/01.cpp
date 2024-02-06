#include <stdint.h>
#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AACENCODER *hAacEncoder = NULL;
  USER_PARAM config;
  memset(&config, 0, sizeof(USER_PARAM));
  int InitFlags = 0;

  hAacEncoder = aacEncOpen(&config, InitFlags);
  if (hAacEncoder == NULL) {
    return 0;
  }
  aacEncInit(hAacEncoder, InitFlags, &config); // Call aacEncInit to initialize the encoder
  FuzzedDataProvider stream(data, size);

  const uint8_t *start = data;
  UINT valid, buffer_size;

  do {
    valid = buffer_size = data + size - start;
    aacEncEncode(hAacEncoder, const_cast<UCHAR **>(&start), &buffer_size, &valid,
                 NULL, NULL);
    start += buffer_size - valid;
  } while (valid > 0);

  aacEncClose(hAacEncoder);
  return 0;
}