#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>
#include "dgif_fuzz_common.h"

extern "C" {
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/message_lite.h"
}

#include "ProtoToGif.h"

using namespace gifProtoFuzzer;

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

DEFINE_PROTO_FUZZER(const PlainTextExtension &plain_text_extension)
{
	// Instantiate ProtoConverter object
	ProtoConverter converter;
	std::string gifRawData = converter.plainTextExtensionToString(plain_text_extension);
	if (const char *dump_path = getenv("PROTO_FUZZER_DUMP_PATH"))
	{
		// With libFuzzer binary run this to generate a GIF from proto:
		// PROTO_FUZZER_DUMP_PATH=x.gif ./fuzzer proto-input
		std::ofstream of(dump_path);
		of.write(gifRawData.data(), gifRawData.size());
	}
	fuzz_dgif_extended((const uint8_t *)gifRawData.data(), gifRawData.size());
}

extern "C" {
PlainTextExtension *PlainTextExtension_CreateMaybeMessage(Arena *arena, PlainTextExtension *from)
{
  return Arena::CreateMaybeMessage<PlainTextExtension>(arena, from);
}

PlainTextExtension *PlainTextExtension_CreateMaybeMessage(Arena *arena)
{
  return Arena::CreateMaybeMessage<PlainTextExtension>(arena);
}

// Add the following line to fix the issue.
PlainTextExtension *PlainTextExtension_CreateMaybeMessage(Arena *arena, const PlainTextExtension *from)
{
  return Arena::CreateMaybeMessage<PlainTextExtension>(arena, from);
}
}