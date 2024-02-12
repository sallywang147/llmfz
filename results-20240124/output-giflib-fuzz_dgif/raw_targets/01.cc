 #include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "ProtoToGif.h"

using namespace gifProtoFuzzer;

DEFINE_PROTO_FUZZER(const GifProto &gif_proto)
{
	// Instantiate ProtoConverter object
	ProtoConverter converter;
	std::string gifRawData = converter.gifProtoToString(gif_proto);
	fuzz_dgif((char *)gifRawData.data(), gifRawData.size());
}