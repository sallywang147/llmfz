#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/pn_transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct pn_transport_t transport;
  struct pn_delivery_t delivery;

  // Initialize the transport and delivery structures
  memset(&transport, 0, sizeof(transport));
  memset(&delivery, 0, sizeof(delivery));

  // Consume a string from the input data
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = str.c_str();

  // Call the target function
  int result = pni_process_tpwork_sender(&transport, &delivery, ptr);

  return 0;
}