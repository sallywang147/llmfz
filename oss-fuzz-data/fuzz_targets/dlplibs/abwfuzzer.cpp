/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * This file is part of the libabw project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cstdint>
#include <cstdlib>

#include <libabw/libabw.h>

#include <librevenge-generators/RVNGDummyTextGenerator.h>

#include <librevenge-stream/librevenge-stream.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  librevenge::RVNGStringStream input(data, size);
  librevenge::RVNGDummyTextGenerator generator;
  libabw::AbiDocument::parse(&input, &generator);
  return 0;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
