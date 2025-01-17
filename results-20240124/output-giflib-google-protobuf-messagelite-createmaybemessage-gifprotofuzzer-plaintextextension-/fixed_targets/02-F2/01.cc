#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include "dgif_fuzz_common.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "ProtoToGif.h"

using namespace gifProtoFuzzer;

extern "C" {
#include "google/protobuf/message_lite.h"
}

DEFINE_PROTO_FUZZER(const GifProto &gif_proto)
{
	// Instantiate ProtoConverter object
	ProtoConverter converter;
	std::string gifRawData = converter.gifProtoToString(gif_proto);
	if (const char *dump_path = getenv("PROTO_FUZZER_DUMP_PATH"))
	{
		// With libFuzzer binary run this to generate a GIF from proto:
		// PROTO_FUZZER_DUMP_PATH=x.gif ./fuzzer proto-input
		std::ofstream of(dump_path);
		of.write(gifRawData.data(), gifRawData.size());
	}
	fuzz_dgif_extended((const uint8_t *)gifRawData.data(), gifRawData.size());
}

DEFINE_PROTO_FUZZER(const PlainTextExtension &plainTextExtension)
{
	// Instantiate ProtoConverter object
	ProtoConverter converter;
	std::string gifRawData = converter.plainTextExtensionToString(plainTextExtension);
	if (const char *dump_path = getenv("PROTO_FUZZER_DUMP_PATH"))
	{
		// With libFuzzer binary run this to generate a GIF from proto:
		// PROTO_FUZZER_DUMP_PATH=x.gif ./fuzzer proto-input
		std::ofstream of(dump_path);
		of.write(gifRawData.data(), gifRawData.size());
	}
	fuzz_dgif_extended((const uint8_t *)gifRawData.data(), gifRawData.size());
}

extern "C"
gifProtoFuzzer::PlainTextExtension * gifProtoFuzzer::PlainTextExtension* google::protobuf::MessageLite::CreateMaybeMessage<gifProtoFuzzer::PlainTextExtension>(google::protobuf::Arena * arena, gifProtoFuzzer::PlainTextExtension * from) {
  return ::google::protobuf::MessageLite::CreateMaybeMessage<gifProtoFuzzer::PlainTextExtension>(arena, from);
}