#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>
#include "dgif_fuzz_common.h"

#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
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

// Fix the build issue by adding the missing function definition
gifProtoFuzzer::PlainTextExtension * gifProtoFuzzer::PlainTextExtension* google::protobuf::MessageLite::CreateMaybeMessage<gifProtoFuzzer::PlainTextExtension>(google::protobuf::Arena * arena, gifProtoFuzzer::PlainTextExtension * from)
{
	return new PlainTextExtension(*from);
}

// Fix the build issue by calling the missing function
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	GifProto gif_proto;
	gif_proto.ParseFromArray(data, size);
	DEFINE_PROTO_FUZZER(gif_proto);
	return 0;
}

DEFINE_PROTO_MUTATOR(PlainTextExtension)
{
	PlainTextExtension *msg = from;
	if (msg == nullptr)
		msg = new PlainTextExtension;
	// Mutate the PlainTextExtension message
	// ...
	return msg;
}