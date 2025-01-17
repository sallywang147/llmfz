#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

namespace itanium_demangle {

class DumpVisitor {
 public:
  void operator()((anonymous namespace)::InitListExpr *Node) {
    // Do nothing.
  }
};

}  // namespace itanium_demangle

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string mangled_name = stream.ConsumeRemainingBytesAsString();
  itanium_demangle::DumpVisitor visitor;
  itanium_demangle::InitListExpr node;
  visitor(&node);
  return 0;
}