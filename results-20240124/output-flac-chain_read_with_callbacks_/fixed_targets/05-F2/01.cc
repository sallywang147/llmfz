#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "FLAC++/metadata.h"
#include "FLAC++/io.h"
#include "FLAC/metadata.h" // Include the necessary header file

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  gdImagePtr slate_image = gdImageCreateTrueColor(slate_width, slate_height);
  if (slate_image == nullptr) {
    return 0;
  }

  const int x_position = stream.ConsumeIntegral<int>();
  const int y_position = stream.ConsumeIntegral<int>();
  const int text_color = stream.ConsumeIntegral<int>();
  const gdFontPtr font_ptr = stream.PickValueInArray(
      {gdFontGetGiant(), gdFontGetLarge(), gdFontGetMediumBold(),
       gdFontGetSmall(), gdFontGetTiny()});
  const std::string text = stream.ConsumeRemainingBytesAsString();

  gdImageString(slate_image, font_ptr, x_position, y_position,
                reinterpret_cast<uint8_t*>(const_cast<char*>(text.c_str())),
                text_color);
  gdImageDestroy(slate_image);

  // Call the target function
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  char *handle = strdup("handle");
  FLAC__IOCallbacks callbacks = {0};
  int is_ogg = 0;
  chain_read_with_callbacks_(chain, handle, &callbacks, is_ogg); // Call the corrected function
  FLAC__metadata_chain_delete(chain);
  free(handle);

  return 0;
}