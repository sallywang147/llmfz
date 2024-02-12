#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>
#include "dgif_fuzz_common.h"

#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "ProtoToGif.h"

#include "google/protobuf/message_lite.h"

using namespace gifProtoFuzzer;

extern "C" {
#include "ProtoToGif.pb.h"
}

DEFINE_PROTO_FUZZER(const BasicChunk &basic_chunk) {
  // Instantiate ProtoConverter object
  ProtoConverter converter;
  std::string gifRawData = converter.basicChunkToString(basic_chunk);
  if (const char *dump_path = getenv("PROTO_FUZZER_DUMP_PATH")) {
    // With libFuzzer binary run this to generate a GIF from proto:
    // PROTO_FUZZER_DUMP_PATH=x.gif ./fuzzer proto-input
    std::ofstream of(dump_path);
    of.write(gifRawData.data(), gifRawData.size());
  }

  // Add the missing function call
  BasicChunk *maybe_message =
      google::protobuf::MessageLite::CreateMaybeMessage<BasicChunk>(nullptr, &basic_chunk);
  fuzz_dgif_extended((const uint8_t *)gifRawData.data(), gifRawData.size());
}