#include <FLAC/seektable.h>
#include <FLAC/cuesheet.h>
#include <FLAC/picture.h>
#include <FLAC/padding.h>

extern "C" {
#include <FLAC/metadata.h>
}

bool FLAC__metadata_chain__read(FLAC__Metadata_Chain *chain, char *handle, FLAC__IOCallbacks *callbacks, bool is_ogg) {
  return FLAC::Metadata::Chain::read(chain, handle, callbacks, is_ogg);
}