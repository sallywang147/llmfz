#include <stddef.h>

#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/link.h>
#include <openthread/message.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/srp_server.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>

#include "common/code_utils.hpp"
#include "common/time.hpp"
#include "fuzzer_platform.h"

namespace ot {

class MeshCoP
{
public:
    class Joiner
    {
    public:
        void TryNextJoinerRouter(int aPrevError)
        {
            // do something
        }
    };
};

}  // namespace ot

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    ot::MeshCoP::Joiner joiner;

    joiner.TryNextJoinerRouter(static_cast<int>(data[0]));

    return 0;
}
}