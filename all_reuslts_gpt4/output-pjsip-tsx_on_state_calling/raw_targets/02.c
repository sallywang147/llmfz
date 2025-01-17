#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pjsip.h"
#include "pjsip/sip_types.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct pjsip_transaction tsx;
  struct pjsip_event event;

  // Initialize pjsip_transaction
  tsx.role = provider.ConsumeEnum<pjsip_role_e>();
  tsx.type = provider.ConsumeEnum<pjsip_type_e>();
  tsx.state = provider.ConsumeEnum<pjsip_state_e>();
  tsx.status_code = provider.ConsumeIntegral<int>();
  tsx.method.id = provider.ConsumeEnum<pjsip_method_e>();
  tsx.method.name.ptr = const_cast<char*>(provider.ConsumeRandomLengthString().c_str());
  tsx.method.name.slen = provider.ConsumeIntegralInRange<int>(0, PJSIP_MAX_URL_SIZE);

  // Initialize pjsip_event
  event.type = provider.ConsumeEnum<pjsip_event_type_e>();
  event.body.tsx_state.type = provider.ConsumeEnum<pjsip_event_type_e>();
  event.body.tsx_state.src_type = provider.ConsumeEnum<pjsip_tsx_state_src_type>();
  event.body.tsx_state.tsx = &tsx;

  // Call the target function
  tsx_on_state_calling(&tsx, &event);

  return 0;
}