#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/flatbuffers.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  const int text_color = stream.ConsumeIntegral<int>();
  const std::string text = stream.ConsumeRemainingBytesAsString();

  flatbuffers::FlatBufferBuilder fbb;
  flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<void>>> offset_vector =
      fbb.CreateVectorOfOffsets(nullptr, 0);
  flatbuffers::Offset<flatbuffers::Vector<uint8_t>> string_vector =
      fbb.CreateVector(reinterpret_cast<const uint8_t*>(text.c_str()), text.size());
  flatbuffers::Type type = flatbuffers::Type::UType_Int32;
  flatbuffers::JsonPrinter printer;
  char* result = printer.PrintVector<flatbuffers::Offset64<void>, unsigned int>(
      &fbb, nullptr, &type, text_color, nullptr);
  free(result);
  return 0;
}