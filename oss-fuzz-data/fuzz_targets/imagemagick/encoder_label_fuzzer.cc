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

#include <Magick++/Blob.h>
#include <Magick++/Image.h>

#include "encoder_utils.cc"
#include "utils.cc"

static bool validateFileName(const std::string &fileName) {
  // Signature: this will most likely cause a timeout.
  if (fileName.find("%#") != -1)
    return (false);

  return (true);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { return (fuzzEncoderWithStringFileName("label", Data, Size, validateFileName)); }
