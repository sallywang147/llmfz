#include <fuzzer/FuzzedDataProvider.h>
#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract a character from the stream
  char c = stream.ConsumeIntegral<char>();

  // Initialize the wc_status struct
  struct wc_status st;
  st.state = stream.ConsumeIntegral<uint32_t>();
  st.design = stream.ConsumeIntegral<uint32_t>();
  st.ucs = stream.ConsumeIntegral<uint32_t>();
  st.ucs_st = stream.ConsumeIntegral<uint32_t>();
  st.ucs_p = stream.ConsumeIntegral<uint32_t>();
  st.ucs4 = stream.ConsumeIntegral<uint32_t>();
  st.ucs4_st = stream.ConsumeIntegral<uint32_t>();
  st.ucs4_p = stream.ConsumeIntegral<uint32_t>();
  st.utf8 = stream.ConsumeIntegral<uint32_t>();
  st.utf8_st = stream.ConsumeIntegral<uint32_t>();
  st.utf8_p = stream.ConsumeIntegral<uint32_t>();
  st.esc = stream.ConsumeIntegral<uint32_t>();
  st.esc_st = stream.ConsumeIntegral<uint32_t>();
  st.esc_p = stream.ConsumeIntegral<uint32_t>();
  st.cr = stream.ConsumeIntegral<uint32_t>();
  st.nl = stream.ConsumeIntegral<uint32_t>();
  st.ss = stream.ConsumeIntegral<uint32_t>();
  st.ss_st = stream.ConsumeIntegral<uint32_t>();
  st.ss_p = stream.ConsumeIntegral<uint32_t>();
  st.ds = stream.ConsumeIntegral<uint32_t>();
  st.ds_st = stream.ConsumeIntegral<uint32_t>();
  st.ds_p = stream.ConsumeIntegral<uint32_t>();

  // Call the function to fuzz
  struct _Str *result = wc_char_conv_from_utf8(c, &st);

  // Cleanup
  if (result != NULL) {
    Strfree(result);
  }

  return 0;
}