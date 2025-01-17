/*
  Copyright @ 2018 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.

  You may not use this file except in compliance with the License.  You may
  obtain a copy of the License at

    https://imagemagick.org/script/license.php

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <cstdint>

#include <Magick++/Image.h>

#include "utils.cc"

namespace MagickCore {
extern "C" void AttachBlob(BlobInfo *, const void *, const size_t);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Magick::ExceptionInfo *exceptionInfo;

  Magick::Image image;

  if (IsInvalidSize(Size, 1, 0))
    return (0);
  MagickCore::AttachBlob(image.image()->blob, (const void *)Data, Size);
  exceptionInfo = MagickCore::AcquireExceptionInfo();
  (void)HuffmanDecodeImage(image.image(), exceptionInfo);
  (void)MagickCore::DestroyExceptionInfo(exceptionInfo);
  return (0);
}
