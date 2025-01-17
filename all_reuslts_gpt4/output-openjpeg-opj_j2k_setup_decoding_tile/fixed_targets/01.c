#include <fuzzer/FuzzedDataProvider.h>
#include <openjpeg.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct opj_procedure_list *procedure_list = opj_procedure_list_create();
  struct opj_event_mgr *event_mgr = new opj_event_mgr();

  opj_j2k_setup_decoding_tile(procedure_list, event_mgr);

  opj_procedure_list_destroy(procedure_list);
  delete event_mgr;

  return 0;
}