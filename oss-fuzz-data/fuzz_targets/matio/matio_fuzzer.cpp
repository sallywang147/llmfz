// Copyright 2019 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Adapter utility from fuzzer input to a temporary file, for fuzzing APIs that
// require a file instead of an input buffer.

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "fuzzer_temp_file.h"
#include "matio_wrap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile temp_file(data, size);

  return MatioRead(temp_file.filename());
}
