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
  if (pCodec == NULL) {
    return 0;
  }
  opj_set_info_handler(pCodec, InfoCallback, NULL);
  opj_set_warning_handler(pCodec, WarningCallback, NULL);
  opj_set_error_handler(pCodec, ErrorCallback, NULL);

  opj_dparameters_t parameters;
  opj_set_default_decoder_parameters(&parameters);

  opj_setup_decoder(pCodec, &parameters);

  opj_stream_t *pStream = opj_stream_create(1024, OPJ_TRUE);
  if (pStream == NULL) {
    opj_destroy_codec(pCodec);
    return 0;
  }
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

  opj_j2k_t *j2k = (opj_j2k_t *)pCodec->j2k;
  opj_event_mgr_t event_mgr;
  memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
  int tile_index = 0;

  opj_j2k_get_tile(j2k, pStream, psImage, &event_mgr, tile_index);

  opj_end_decompress(pCodec, pStream);
  opj_stream_destroy(pStream);
  opj_destroy_codec(pCodec);
  opj_image_destroy(psImage);

  return 0;
}