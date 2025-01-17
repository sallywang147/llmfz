//===-- get_error_info_fuzzer.cpp -----------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#define SCUDO_FUZZ
#include "allocator_config.h"
#include "combined.h"

#include <fuzzer/FuzzedDataProvider.h>

#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(uint8_t *Data, size_t Size) {
  using AllocatorT = scudo::Allocator<scudo::AndroidConfig>;
  FuzzedDataProvider FDP(Data, Size);

  uintptr_t FaultAddr = FDP.ConsumeIntegral<uintptr_t>();
  uintptr_t MemoryAddr = FDP.ConsumeIntegral<uintptr_t>();

  std::string MemoryAndTags = FDP.ConsumeRandomLengthString(FDP.remaining_bytes());
  const char *Memory = MemoryAndTags.c_str();
  // Assume 16-byte alignment.
  size_t MemorySize = (MemoryAndTags.length() / 17) * 16;
  const char *MemoryTags = Memory + MemorySize;

  std::string StackDepotBytes = FDP.ConsumeRandomLengthString(FDP.remaining_bytes());
  std::vector<char> StackDepot(sizeof(scudo::StackDepot), 0);
  for (size_t i = 0; i < StackDepotBytes.length() && i < StackDepot.size(); ++i) {
    StackDepot[i] = StackDepotBytes[i];
  }

  std::string RegionInfoBytes = FDP.ConsumeRandomLengthString(FDP.remaining_bytes());
  std::vector<char> RegionInfo(AllocatorT::getRegionInfoArraySize(), 0);
  for (size_t i = 0; i < RegionInfoBytes.length() && i < RegionInfo.size(); ++i) {
    RegionInfo[i] = RegionInfoBytes[i];
  }

  std::string RingBufferBytes = FDP.ConsumeRemainingBytesAsString();
  std::vector<char> RingBuffer(AllocatorT::getRingBufferSize(), 0);
  for (size_t i = 0; i < RingBufferBytes.length() && i < RingBuffer.size(); ++i) {
    RingBuffer[i] = RingBufferBytes[i];
  }

  scudo_error_info ErrorInfo;
  AllocatorT::getErrorInfo(&ErrorInfo, FaultAddr, StackDepot.data(), RegionInfo.data(), RingBuffer.data(), Memory, MemoryTags, MemoryAddr, MemorySize);
  return 0;
}
