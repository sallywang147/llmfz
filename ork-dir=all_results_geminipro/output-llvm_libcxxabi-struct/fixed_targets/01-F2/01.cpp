#include <itanium_demangle.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <itanium_demangle.h>
}

struct DumpVisitor {
  void Dump(itanium_demangle::InitListExpr *Node) {
    // Do nothing.
  }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  DumpVisitor visitor;
  visitor.Dump(reinterpret_cast<itanium_demangle::InitListExpr*>(
      const_cast<char*>(text.c_str())));
  return 0;
}