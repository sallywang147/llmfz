#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <FLAC/stream_decoder.h>
#include <FLAC/metadata.h>
}

using namespace FLAC;
using namespace fuzzer;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  Metadata::Chain chain;
  if (!chain.read(fdp.ConsumeRemainingBytes(), nullptr, nullptr, false)) {
    return 0;
  }

  Metadata::Iterator it = chain.metadata();
  while (it.is_valid()) {
    Metadata::Type type = it.get_block_type();
    if (type == Metadata::Type::StreamInfo) {
      Metadata::StreamInfo info = it.get_stream_info();
      (void)info;
    } else if (type == Metadata::Type::SeekTable) {
      Metadata::SeekTable table = it.get_seek_table();
      (void)table;
    } else if (type == Metadata::Type::Application) {
      Metadata::Application app = it.get_application();
      (void)app;
    } else if (type == Metadata::Type::VorbisComment) {
      Metadata::VorbisComment comment = it.get_vorbis_comment();
      (void)comment;
    } else if (type == Metadata::Type::CueSheet) {
      Metadata::CueSheet sheet = it.get_cue_sheet();
      (void)sheet;
    } else if (type == Metadata::Type::Picture) {
      Metadata::Picture picture = it.get_picture();
      (void)picture;
    } else if (type == Metadata::Type::Padding) {
      Metadata::Padding padding = it.get_padding();
      (void)padding;
    } else if (type == Metadata::Type::Unknown) {
      Metadata::Unknown unknown = it.get_unknown();
      (void)unknown;
    }

    it.next();
  }

  return 0;
}