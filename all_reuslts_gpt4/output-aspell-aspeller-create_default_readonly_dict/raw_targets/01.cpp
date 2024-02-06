#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aspell.h"
#include "posib_err.hpp"
#include "config.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  acommon::PosibErr<aspell::Speller *> els;
  acommon::Config config;
  aspell::Speller speller(&config);
  
  std::vector<char> stringEnumerationData = stream.ConsumeBytes<char>(stream.remaining_bytes());
  AspellStringEnumeration stringEnumeration { stringEnumerationData.size(), stringEnumerationData.data() };
  
  speller.create_default_readonly_dict(&els, &stringEnumeration, &config);
  
  return 0;
}