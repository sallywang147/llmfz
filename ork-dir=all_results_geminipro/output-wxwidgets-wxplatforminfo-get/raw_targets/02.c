#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wx/platform.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  wxPlatformInfo *platform_info = wxPlatformInfo::Get();
  if (platform_info == nullptr) {
    return 0;
  }

  platform_info->SetOperatingSystemId(wxOS_WINDOWS);

  FuzzedDataProvider provider(data, size);
  const size_t num_cpus = provider.ConsumeIntegralInRange<size_t>(1, 100);
  platform_info->SetNumberOfCpus(num_cpus);

  const size_t memory_size = provider.ConsumeIntegralInRange<size_t>(1, 1024);
  platform_info->SetMemorySize(memory_size);

  const size_t num_disks = provider.ConsumeIntegralInRange<size_t>(1, 10);
  platform_info->SetNumberOfDisks(num_disks);

  const size_t num_displays = provider.ConsumeIntegralInRange<size_t>(1, 10);
  platform_info->SetNumberOfDisplays(num_displays);

  const size_t num_printers = provider.ConsumeIntegralInRange<size_t>(1, 10);
  platform_info->SetNumberOfPrinters(num_printers);

  platform_info->SetArchitecture(wxARCH_32);

  platform_info->SetEndianness(wxENDIAN_LITTLE);

  return 0;
}