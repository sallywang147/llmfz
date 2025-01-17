#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class/msc/msc_device.h"
#include "fuzz/fuzz.h"
#include "tusb.h"
#include <cstdint>
#include <string>
#include <vector>

extern "C" {

#define FUZZ_ITERATIONS 500

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

void msc_task(FuzzedDataProvider *provider);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider provider(Data, Size);
  std::vector<uint8_t> callback_data = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, Size));
  fuzz_init(callback_data.data(), callback_data.size());
  // init device stack on configured roothub port
  tud_init(BOARD_TUD_RHPORT);

  for (int i = 0; i < FUZZ_ITERATIONS; i++) {
    if (provider.remaining_bytes() == 0) {
      return 0;
    }
    tud_int_handler(provider.ConsumeIntegral<uint8_t>());
    tud_task(); // tinyusb device task
    msc_task(&provider);
  }

  return 0;
}

//--------------------------------------------------------------------+
// USB MSC
//--------------------------------------------------------------------+
enum MscApiFuncs {
  kMscReset,
  kMscGetMaxLun,
  kMscInquiry,
  kMscReadCapacity,
  kMscRead10,
  kMscWrite10,
  kMscTestUnitReady,
  kMscRequestSense,
  kMscFormat,
  kMscGetConfiguration,
  kMscSetConfiguration,
  kMscGetMaxLun,
  kMscMassStorageReset,
  kMscGetStatus,
  kMscStall,
  kMaxValue,
};

void msc_task(FuzzedDataProvider *provider) {

  assert(provider != NULL);
  switch (provider->ConsumeEnum<MscApiFuncs>()) {

  case kMscReset:
    msc_reset();
    break;
  case kMscGetMaxLun:
    msc_get_max_lun();
    break;
  case kMscInquiry:
    msc_inquiry(provider->ConsumeIntegral<uint8_t>(),
                provider->ConsumeIntegral<uint8_t>(),
                provider->ConsumeBytes<uint8_t>(36).data());
    break;
  case kMscReadCapacity:
    msc_read_capacity(provider->ConsumeIntegral<uint8_t>(),
                      provider->ConsumeBytes<uint8_t>(8).data());
    break;
  case kMscRead10:
    msc_read10(provider->ConsumeIntegral<uint8_t>(),
               provider->ConsumeIntegral<uint32_t>(),
               provider->ConsumeIntegral<uint16_t>(),
               provider->ConsumeBytes<uint8_t>(512).data());
    break;
  case kMscWrite10:
    msc_write10(provider->ConsumeIntegral<uint8_t>(),
                provider->ConsumeIntegral<uint32_t>(),
                provider->ConsumeIntegral<uint16_t>(),
                provider->ConsumeBytes<uint8_t>(512).data());
    break;
  case kMscTestUnitReady:
    msc_test_unit_ready(provider->ConsumeIntegral<uint8_t>());
    break;
  case kMscRequestSense:
    msc_request_sense(provider->ConsumeIntegral<uint8_t>(),
                      provider->ConsumeBytes<uint8_t>(18).data());
    break;
  case kMscFormat:
    msc_format(provider->ConsumeIntegral<uint8_t>());
    break;
  case kMscGetConfiguration:
    msc_get_configuration(provider->ConsumeIntegral<uint8_t>(),
                          provider->ConsumeBytes<uint8_t>(8).data());
    break;
  case kMscSetConfiguration:
    msc_set_configuration(provider->ConsumeIntegral<uint8_t>(),
                          provider->ConsumeBytes<uint8_t>(8).data());
    break;
  case kMscMassStorageReset:
    msc_mass_storage_reset();
    break;
  case kMscGetStatus:
    msc_get_status(provider->ConsumeIntegral<uint8_t>(),
                   provider->ConsumeBytes<uint8_t>(4).data());
    break;
  case kMscStall:
    msc_stall(provider->ConsumeIntegral<uint8_t>());
    break;
  case kMaxValue:
    // Noop.
    break;
  }
}

//--------------------------------------------------------------------+
// SCSI Commands
//--------------------------------------------------------------------+
enum ScsiCmd {
  kScsiInquiry,
  kScsiReadCapacity,
  kScsiRead10,
  kScsiWrite10,
  kScsiTestUnitReady,
  kScsiRequestSense,
  kScsiFormat,
  kScsiGetConfiguration,
  kScsiSetConfiguration,
  kScsiGetMaxLun,
  kScsiMassStorageReset,
  kScsiGetStatus,
  kScsiStall,
  kMaxValue,
};

bool mscd_xfer_cb(char lun, char cmd, int dir, int len) {
  assert(lun < MSC_MAX_LUN);

  (void)len;

  switch (cmd) {
  case kScsiInquiry:
    msc_inquiry(lun, dir, msc_cbw.CB.CB_CBData);
    break;
  case kScsiReadCapacity:
    msc_read_capacity(lun, msc_cbw.CB.CB_CBData);
    break;
  case kScsiRead10:
    msc_read10(lun, msc_cbw.CB.CB_CBData[2], msc_cbw.CB.CB_CBData[7],
               msc_cbw.CB.CB_CBData);
    break;
  case kScsiWrite10:
    msc_write10(lun, msc_cbw.CB.CB_CBData[2], msc_cbw.CB.CB_CBData[7],
                msc_cbw.CB.CB_CBData);
    break;
  case kScsiTestUnitReady:
    msc_test_unit_ready(lun);
    break;
  case kScsiRequestSense:
    msc_request_sense(lun, msc_cbw.CB.CB_CBData);
    break;
  case kScsiFormat:
    msc_format(lun);
    break;
  case kScsiGetConfiguration:
    msc_get_configuration(lun, msc_cbw.CB.CB_CBData);
    break;
  case kScsiSetConfiguration:
    msc_set_configuration(lun, msc_cbw.CB.CB_CBData);
    break;
  case kScsiGetMaxLun:
    msc_get_max_lun();
    break;
  case kScsiMassStorageReset:
    msc_mass_storage_reset();
    break;
  case kScsiGetStatus:
    msc_get_status(lun, msc_cbw.CB.CB_CBData);
    break;
  case kScsiStall:
    msc_stall(lun);
    break;
  case kMaxValue:
    // Noop.
    break;
  }

  return true;
}

}