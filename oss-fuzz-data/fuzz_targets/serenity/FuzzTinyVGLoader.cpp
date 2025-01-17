/*
 * Copyright (c) 2023, MacDue <macdue@dueutil.tech>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGfx/ImageFormats/TinyVGLoader.h>

extern "C" int LLVMFuzzerTestOneInput(uint8_t const *data, size_t size) {
  AK::set_debug_enabled(false);
  auto decoder_or_error = Gfx::TinyVGImageDecoderPlugin::create({data, size});
  if (decoder_or_error.is_error())
    return 0;
  auto decoder = decoder_or_error.release_value();
  (void)decoder->frame(0);
  return 0;
}
