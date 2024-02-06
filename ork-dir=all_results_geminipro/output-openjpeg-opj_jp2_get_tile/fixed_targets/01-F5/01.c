#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "openjpeg.h"

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv);
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len);

typedef struct {
  const uint8_t *pabyData;
  size_t nCurPos;
  size_t nLength;
} MemFile;

static void ErrorCallback(const char *msg, void *) {
  (void)msg;
  // fprintf(stderr, "%s\n", msg);
}

static void WarningCallback(const char *, void *) {}

static void InfoCallback(const char *, void *) {}

static OPJ_SIZE_T ReadCallback(void *pBuffer, OPJ_SIZE_T nBytes, void *pUserData) {
  MemFile *memFile = (MemFile *)pUserData;
  // printf("want to read %d bytes at %d\n", (int)memFile->nCurPos, (int)nBytes);
  if (memFile->nCurPos >= memFile->nLength) {
    return -1;
  }
  if (memFile->nCurPos + nBytes >= memFile->nLength) {
    size_t nToRead = memFile->nLength - memFile->nCurPos;
    memcpy(pBuffer, memFile->pabyData + memFile->nCurPos, nToRead);
    memFile->nCurPos = memFile->nLength;
    return nToRead;
  }
  if (nBytes == 0) {
    return -1;
  }
  memcpy(pBuffer, memFile->pabyData + memFile->nCurPos, nBytes);
  memFile->nCurPos += nBytes;
  return nBytes;
}

static OPJ_BOOL SeekCallback(OPJ_OFF_T nBytes, void *pUserData) {
  MemFile *memFile = (MemFile *)pUserData;
  // printf("seek to %d\n", (int)nBytes);
  memFile->nCurPos = nBytes;
  return OPJ_TRUE;
}

static OPJ_OFF_T SkipCallback(OPJ_OFF_T nBytes, void *pUserData) {
  MemFile *memFile = (MemFile *)pUserData;
  memFile->nCurPos += nBytes;
  return nBytes;
}

int LLVMFuzzerInitialize(int * /*argc*/, char ***argv) { return 0; }

static const unsigned char jpc_header[] = {0xff, 0x4f};
static const unsigned char jp2_box_jp[] = {0x6a, 0x50, 0x20, 0x20}; /* 'jP  ' */

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {

  OPJ_CODEC_FORMAT eCodecFormat;
  if (len >= 4 + sizeof(jp2_box_jp) && memcmp(buf + 4, jp2_box_jp, sizeof(jp2_box_jp)) == 0) {
    eCodecFormat = OPJ_CODEC_JP2;
  } else {
    return 0;
  }

  opj_codec_t *pCodec = opj_create_decompress(eCodecFormat);
  opj_set_info_handler(pCodec, InfoCallback, NULL);
  opj_set_warning_handler(pCodec, WarningCallback, NULL);
  opj_set_error_handler(pCodec, ErrorCallback, NULL);

  opj_dparameters_t parameters;
  opj_set_default_decoder_parameters(&parameters);

  opj_setup_decoder(pCodec, &parameters);

  opj_stream_t *pStream = opj_stream_create(1024, OPJ_TRUE);
  MemFile memFile;
  memFile.pabyData = buf;
  memFile.nLength = len;
  memFile.nCurPos = 0;
  opj_stream_set_user_data_length(pStream, len);
  opj_stream_set_read_function(pStream, ReadCallback);
  opj_stream_set_seek_function(pStream, SeekCallback);
  opj_stream_set_skip_function(pStream, SkipCallback);
  opj_stream_set_user_data(pStream, &memFile, NULL);

  opj_image_t *psImage = NULL;
  if (!opj_read_header(pStream, pCodec, &psImage)) {
    opj_destroy_codec(pCodec);
    opj_stream_destroy(pStream);
    opj_image_destroy(psImage);
    return 0;
  }

  OPJ_UINT32 width = psImage->x1 - psImage->x0;
  OPJ_UINT32 height = psImage->y1 - psImage->y0;

  OPJ_UINT32 width_to_read = width;
  if (width_to_read > 1024) {
    width_to_read = 1024;
  }
  OPJ_UINT32 height_to_read = height;
  if (height_to_read > 1024) {
    height_to_read = 1024;
  }

  if (opj_set_decode_area(pCodec, psImage, psImage->x0, psImage->y0, psImage->x0 + width_to_read, psImage->y0 + height_to_read)) {
    if (opj_decode(pCodec, pStream, psImage)) {
      // printf("success\n");
    }
  }

  opj_jp2_get_tile(pCodec->jp2_decoder, pStream->p_j2k, psImage, NULL, 0);

  opj_end_decompress(pCodec, pStream);
  opj_stream_destroy(pStream);
  opj_destroy_codec(pCodec);
  opj_image_destroy(psImage);

  return 0;
}