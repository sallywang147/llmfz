#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "openjpeg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenJPEG library
  opj_initialize();

  // Create a procedure list and an event manager
  struct opj_procedure_list *procedure_list = opj_procedure_list_create();
  struct opj_event_mgr *event_mgr = (opj_event_mgr *) malloc(sizeof(opj_event_mgr));

  // Call the target function
  int result = opj_j2k_setup_decoding_tile(procedure_list, event_mgr);

  // Cleanup
  opj_procedure_list_destroy(procedure_list);
  free(event_mgr);

  return 0;
}