#include "RawImage.h"
#include "NakedDecoder.h"
#include "RawDecoder.h"
#include "io/ByteStream.h"
#include "io/Endianness.h"
#include "io/File.h"
#include "io/FileBuffer.h"
#include "io/IOException.h"
#include "io/MemoryBuffer.h"
#include "io/Stream.h"
#include "io/StreamBuffer.h"
#include "io/StreamFile.h"
#include "io/StreamMemory.h"
#include "io/StreamString.h"
#include "io/StreamVector.h"
#include "io/StringStream.h"
#include "io/VectorStream.h"
#include "io/VectorStreamBuffer.h"
#include "io/VectorStreamFile.h"
#include "io/VectorStreamMemory.h"
#include "io/VectorStreamString.h"
#include "io/VectorStreamVector.h"
#include "codes/PrefixCodeDecoder.h"
#include "codes/PrefixCodeDecoder/Common.h"
#include "codes/PrefixCodeLUTDecoder.h"
#include "codes/PrefixCodeLookupDecoder.h"
#include "codes/PrefixCodeTreeDecoder.h"
#include "codes/PrefixCodeVectorDecoder.h"

extern "C" {
#include "codes/PrefixCodeDecoder/Common.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  rawspeed::RawImage rawImage;
  rawspeed::NakedDecoder nakedDecoder;
  nakedDecoder.decodeRawInternal(&rawImage, &nakedDecoder, data, size);
  return 0;
}