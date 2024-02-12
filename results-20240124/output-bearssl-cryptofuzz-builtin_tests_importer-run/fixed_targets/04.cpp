#include <cryptofuzz/options.h>
#include <fuzzing/datasource/id.hpp>
#include <repository_tbl.h>
#include <driver.h>
#include <numbers.h>
#include <mutatorpool.h>

extern "C" {
#include <LLVMFuzzerTestOneInput.h>
}

namespace cryptofuzz {

void Builtin_tests_importer::Run(union anon *data) {
  // ...
}

}  // namespace cryptofuzz

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cryptofuzz::Builtin_tests_importer::Run((union anon *)data);
  return 0;
}