#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "libdwarf.h"

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

  // Call dwfl_frame_pc to fix the build error
  struct Dwfl_Frame state;
  size_t pc;
  char isactivation;
  dwfl_frame_pc(&state, &pc, &isactivation);

  gdImageDestroy(slate_image);
  return 0;
}