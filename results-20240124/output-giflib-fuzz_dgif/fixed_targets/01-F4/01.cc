#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "port/protobuf.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "ProtoToGif.h"

extern "C" {
#include "dgif_lib.h"
}

using namespace gifProtoFuzzer;

DEFINE_PROTO_FUZZER(const GifProto &gif_proto)
{
	// Instantiate ProtoConverter object
	ProtoConverter converter;
	std::string gifRawData = converter.gifProtoToString(gif_proto);
	fuzz_dgif((char *)gifRawData.data(), gifRawData.size());
}