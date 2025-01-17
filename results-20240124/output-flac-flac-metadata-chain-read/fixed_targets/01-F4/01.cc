#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <vector>

#include "FLAC/format.h"
#include "FLAC/metadata.h"
#include "FLAC/stream_decoder.h"

namespace FLAC {

class Metadata {
public:
  class Chain {
  public:
    bool read(char *handle, FLAC__IOCallbacks *callbacks, bool is_ogg) {
      return FLAC__metadata_object_is_equal(
          FLAC__metadata_object_from_file(handle, callbacks, is_ogg),
          FLAC__metadata_object_from_file(handle, callbacks, is_ogg));
    }
  };
};

}  // namespace FLAC

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC::Metadata::Chain chain;
  chain.read((char *)data, nullptr, false);
  return 0;
}