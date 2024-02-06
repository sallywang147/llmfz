#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "secmod.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct SECMODModuleStr module;

  // Fill the module struct with fuzzed data
  module.commonName = stream.ConsumeRandomLengthString().c_str();
  module.dllName = stream.ConsumeRandomLengthString().c_str();
  module.libraryParams = stream.ConsumeRandomLengthString().c_str();
  module.URI = stream.ConsumeRandomLengthString().c_str();
  module.moduleDBFunc = reinterpret_cast<void*>(stream.ConsumeIntegral<uintptr_t>());
  module.internal = stream.ConsumeBool();
  module.fips = stream.ConsumeBool();
  module.loaded = stream.ConsumeBool();
  module.isFIPS = stream.ConsumeBool();
  module.parent = reinterpret_cast<SECMODModule*>(stream.ConsumeIntegral<uintptr_t>());
  module.library = reinterpret_cast<SECMODModule*>(stream.ConsumeIntegral<uintptr_t>());
  module.functionList = reinterpret_cast<SECMODModule*>(stream.ConsumeIntegral<uintptr_t>());
  module.slotCount = stream.ConsumeIntegral<unsigned long>();
  module.slots = reinterpret_cast<PK11SlotInfo**>(stream.ConsumeIntegral<uintptr_t>());
  module.ssl[0] = reinterpret_cast<SSL3StatisticsStr*>(stream.ConsumeIntegral<uintptr_t>());
  module.ssl[1] = reinterpret_cast<SSL3StatisticsStr*>(stream.ConsumeIntegral<uintptr_t>());
  module.internal = stream.ConsumeBool();
  module.isModuleDB = stream.ConsumeBool();
  module.moduleDBOnly = stream.ConsumeBool();
  module.trustOrder = stream.ConsumeIntegral<unsigned long>();
  module.cipherOrder = stream.ConsumeIntegral<unsigned long>();
  module.evControlMask = stream.ConsumeIntegral<unsigned long>();

  // Call the function to fuzz
  vcard_emul_new_event_thread(&module);

  return 0;
}