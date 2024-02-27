#include <stddef.h>
#include <stdint.h>

#include "FLAC/metadata.h"

extern "C" {
#include "FLAC/stream_decoder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  FLAC__IOCallbacks callbacks = {0};
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_SEEKTABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CODEC_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_CONTAINER_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_PICTURE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_APPLICATION);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ICY);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_XIPH_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_TABLE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CUESHEET);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_LYRICS);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_STREAMINFO);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PADDING);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_PROBE);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_REPLAY_GAIN);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_SEEK_POINT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_VORBIS_COMMENT);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC_INFO_METADATA_BLOCK);
  FLAC__stream_decoder_set_metadata_respond(decoder, FLAC__METADATA_TYPE_ANDROID_CODEC_INFO_METADATA_BLOCK_ANDROID_CODEC