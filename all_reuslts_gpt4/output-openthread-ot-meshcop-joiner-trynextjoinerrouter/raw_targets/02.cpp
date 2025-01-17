#include <stddef.h>
#include <stdint.h>

#include <openthread/instance.h>
#include <openthread/joiner.h>

#include "common/code_utils.hpp"
#include "common/instance.hpp"
#include "meshcop/joiner.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ot::Instance *instance = nullptr;
  ot::MeshCoP::Joiner *joiner = nullptr;
  int prevError = 0;

  if (size < sizeof(int)) {
    return 0;
  }

  instance = new ot::Instance();
  joiner = &instance->Get<ot::MeshCoP::Joiner>();

  memcpy(&prevError, data, sizeof(int));
  data += sizeof(int);
  size -= sizeof(int);

  joiner->TryNextJoinerRouter(prevError);

  delete instance;

  return 0;
}