#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "pb.h"

extern "C" {
#include "pb_decode.h"
#include "pb_encode.h"
}

struct pb_msgdesc_s {
  uint32_t size;
  const char *name;
  const pb_field_t *fields;
};

extern "C" bool pb_get_encoded_size(size_t *size, struct pb_msgdesc_s *fields, char *src_struct) {
  return pb_get_encoded_size(size, fields, src_struct);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  struct pb_msgdesc_s fields;
  char src_struct[1024];
  size_t encoded_size;
  if (!pb_get_encoded_size(&encoded_size, &fields, src_struct)) {
    return 0;
  }
  char *encoded_data = new char[encoded_size];
  pb_encode(&fields, src_struct, encoded_data);
  delete[] encoded_data;
  return 0;
}