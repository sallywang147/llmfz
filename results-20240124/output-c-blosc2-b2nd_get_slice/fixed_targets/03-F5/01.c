#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "b2nd.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef __cplusplus
extern "C" {
#endif

#include "blosc.h"
#include "blosclz.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int32_t i = 0, dsize = 0, filter = BLOSC_BITSHUFFLE;
  int32_t nchunk = 0, max_chunksize = 512;
  int64_t nchunks = 0;

  b2nd_init();

  b2nd_cparams cparams = BLOSC2_CPARAMS_DEFAULTS;
  cparams.typesize = 1;
  /* Find next available compressor */
  cparams.compcode = 0;
  while (blosc1_set_compressor(compressors[cparams.compcode % 6]) == -1 && i < 6) {
    cparams.compcode++, i++;
  }
  if (i == 6) {
    /* No compressors available */
    b2nd_destroy();
    return 0;
  }
  if (size > INT32_MAX) {
      printf("Conversion error: size_t does not fit in int32_t\n");
      return 0;
  }
  if (size > 0) {
    /* Variable size compression level and max chunksize */
    cparams.clevel = data[0] % (9 + 1);
    max_chunksize *= data[0];
  }
  if (size > 1) {
    filter = data[1];
  }
  cparams.filters[BLOSC2_MAX_FILTERS - 1] = filter % (BLOSC_BITSHUFFLE + 1);
  cparams.filters_meta[BLOSC2_MAX_FILTERS - 1] = filter;
  cparams.nthreads = 1;

  b2nd_dparams dparams = BLOSC2_DPARAMS_DEFAULTS;
  dparams.nthreads = 1;

  /* Create a super-chunk backed by an in-memory frame */
  b2nd_storage storage = {.cparams = &cparams, .dparams = &dparams};
  b2nd_schunk *schunk = b2nd_schunk_new(&storage);
  if (schunk == NULL) {
    b2nd_destroy();
    return 0;
  }

  /* Compress data */
  int32_t chunksize = max_chunksize;
  for (i = 0; chunksize > 0 && i < (int32_t)size; i += chunksize, nchunks++) {
    if (i + chunksize > (int32_t)size)
      chunksize = (int32_t)size - i;
    nchunks = b2nd_schunk_append_buffer(schunk, (uint8_t *)data + i, chunksize);
    if (nchunks < 0) {
      printf("Compression error.  Error code: %" PRId64 "\n", nchunks);
      break;
    }
  }

  /* Decompress data */
  uint8_t *uncompressed_data = (uint8_t *)malloc(size + 1);
  if (uncompressed_data != NULL) {
    for (i = 0, nchunk = 0; nchunk < nchunks - 1; nchunk++) {
      dsize = b2nd_schunk_decompress_chunk(schunk, nchunk, uncompressed_data + i, chunksize);
      if (dsize < 0) {
        printf("Decompression error.  Error code: %d\n", dsize);
        break;
      }
      i += dsize;
    }

    /* Compare decompressed data with original */
    if (size > 0 && nchunks > 0) {
      if (dsize < 0 || memcmp(data, uncompressed_data, size) != 0) {
        printf("Decompression data does not match original %d\n", dsize);
      }
    }

    free(uncompressed_data);
  }

  /* Get slice */
  struct b2nd_array_t *array = NULL;
  struct b2nd_array_t.161 *array161 = NULL;
  size_t start[1], size[1];
  start[0] = 0;
  size[0] = 1;
  int ret = b2nd_get_slice(schunk->context, &array161, array, start, size);
  if (ret < 0) {
    printf("Error getting slice: %d\n", ret);
  }

  /* Free resources */
  b2nd_schunk_free(schunk);

  b2nd_destroy();
  return 0;
}

#ifdef __cplusplus
}
#endif