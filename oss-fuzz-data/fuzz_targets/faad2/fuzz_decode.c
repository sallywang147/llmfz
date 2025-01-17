/*
** FAAD2 - Freeware Advanced Audio (AAC) Decoder including SBR decoding
** Copyright (C) 2003-2005 M. Bakker, Nero AG, http://www.nero.com
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** Any non-GPL usage of this software or parts of this software is strictly
** forbidden.
**
** The "appropriate copyright message" mentioned in section 2c of the GPLv2
** must read: "Code from FAAD2 is copyright (c) Nero AG, www.nero.com"
**
** Commercial non-GPL licensing of this software is possible.
** For more info contact Nero AG through Mpeg4AAClicense@nero.com.
**/

#include <fenv.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "neaacdec.h"

int feenableexcept(int excepts);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t preamble = 2 + 2 + 1 + sizeof(NeAACDecConfiguration);
  NeAACDecConfiguration config;
  uint64_t sample_rate;
  unsigned char num_channels;
  NeAACDecConfigurationPtr config_ptr;
  /* feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW); */

  if (size < preamble)
    return 0;
  size_t len1 = data[0] | (data[1] << 8);
  data += 2;
  size_t len2 = data[0] | (data[1] << 8);
  data += 2;
  uint8_t flags = data[0];
  data += 1;
  memcpy(&config, data, sizeof(NeAACDecConfiguration));
  data += sizeof(NeAACDecConfiguration);
  size -= preamble;

  if (len1 + len2 > size)
    return 0;
  size_t len3 = size - len1 - len2;
  int use_init2 = flags & 1;
  int seek_before = flags & 2;
  int seek_between = flags & 4;
  size_t buffer_op = (flags >> 3) & 3;
  int use_drm = flags & 32;
  int drm_channels = (flags >> 5) & 7;
  unsigned long drm_sample_rate = config.defSampleRate;
  int res, ok;
  const size_t kBufferSize[4] = {0, 0, 16, 16384};
  size_t buffer_size = kBufferSize[buffer_op];
  void *buffer = buffer_size > 0 ? (unsigned char *)malloc(buffer_size) : NULL;

  unsigned char *part1 = (unsigned char *)malloc(len1);
  unsigned char *part2 = (unsigned char *)malloc(len2);
  unsigned char *part3 = (unsigned char *)malloc(len3);
  memcpy(part1, data, len1);
  data += len1;
  memcpy(part2, data, len2);
  data += len2;
  memcpy(part3, data, len3);
  data += len3;

  NeAACDecHandle decoder = NeAACDecOpen();
  ok = NeAACDecSetConfiguration(decoder, &config);
  if (!ok)
    goto cleanup;
  config_ptr = NeAACDecGetCurrentConfiguration(decoder);
  if (!config_ptr)
    __builtin_trap();
  if (use_init2) {
    res = NeAACDecInit2(decoder, part1, len1, &sample_rate, &num_channels);
  } else {
    res = NeAACDecInit(decoder, part1, len1, &sample_rate, &num_channels);
  }
  if (use_drm) {
#ifdef DRM_SUPPORT
    NeAACDecInitDRM(&decoder, drm_channels, drm_sample_rate);
#else
    (void)drm_channels;
    (void)drm_sample_rate;
#endif
  }

  if (res != 0)
    goto cleanup;
  NeAACDecFrameInfo faad_info;
  if (seek_before) {
    NeAACDecPostSeekReset(decoder, 0x1234567);
  }
  NeAACDecDecode(decoder, &faad_info, part2, len2);
  if (seek_between) {
    NeAACDecPostSeekReset(decoder, -0x1234567);
  }
  if (buffer_op == 0) {
    NeAACDecDecode(decoder, &faad_info, part3, len3);
  } else {
    NeAACDecDecode2(decoder, &faad_info, part3, len3, &buffer, buffer_size);
  }

cleanup:
  NeAACDecClose(decoder);
  free(part1);
  free(part2);
  free(part3);
  if (buffer)
    free(buffer);

  return 0;
}
