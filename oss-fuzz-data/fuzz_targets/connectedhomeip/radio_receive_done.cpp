/*
 *  Copyright (c) 2017, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <string.h>

#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/link.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/radio.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>

#include "common/code_utils.hpp"
#include "common/time.hpp"
#include "fuzzer_platform.h"

void AdvanceTime(otInstance *aInstance, uint32_t aDuration) {
  uint32_t time = otPlatAlarmMilliGetNow() + aDuration;

  while (ot::TimeMilli(otPlatAlarmMilliGetNow()) <= ot::TimeMilli(time)) {
    while (otTaskletsArePending(aInstance)) {
      otTaskletsProcess(aInstance);
    }

    FuzzerPlatformProcess(aInstance);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const otPanId panId = 0xdead;

  otInstance *instance = nullptr;
  otRadioFrame frame;
  uint8_t *buf = nullptr;

  VerifyOrExit(size <= OT_RADIO_FRAME_MAX_SIZE);

  FuzzerPlatformInit();

  instance = otInstanceInitSingle();
  IgnoreError(otLinkSetPanId(instance, panId));
  IgnoreError(otIp6SetEnabled(instance, true));
  IgnoreError(otThreadSetEnabled(instance, true));
  IgnoreError(otThreadBecomeLeader(instance));

  AdvanceTime(instance, 10000);

  buf = static_cast<uint8_t *>(malloc(size));
  memset(&frame, 0, sizeof(frame));
  frame.mPsdu = buf;
  frame.mChannel = 11;
  frame.mLength = static_cast<uint8_t>(size);
  memcpy(buf, data, frame.mLength);

  otPlatRadioReceiveDone(instance, &frame, OT_ERROR_NONE);

  VerifyOrExit(!FuzzerPlatformResetWasRequested());

  AdvanceTime(instance, 10000);

exit:

  if (buf != nullptr) {
    free(buf);
  }

  if (instance != nullptr) {
    otInstanceFinalize(instance);
  }

  return 0;
}
