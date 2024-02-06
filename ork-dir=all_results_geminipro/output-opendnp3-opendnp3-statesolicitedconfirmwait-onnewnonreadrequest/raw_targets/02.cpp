#include <opendnp3/master/MasterApplication.h>
#include <opendnp3/master/MasterContext.h>
#include <opendnp3/master/StateSolicitedConfirmWait.h>

#include <dnp3mocks/MockMasterApplication.h>
#include <dnp3mocks/MockOContext.h>
#include <dnp3mocks/MockParsedRequest.h>

#include <ser4cpp/rseq_t.h>

#include "NullLogHandler.h"

class MasterTestObject {
public:
  MasterTestObject(const opendnp3::MasterParams &params) : addresses(), logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), application(std::make_shared<MockMasterApplication>()), context(opendnp3::MContext::Create(addresses, logger.get_logger(), exe, nullptr, nullptr, application, nullptr, params)) {}

  ~MasterTestObject() { this->scheduler->Shutdown(); }

  size_t SendToMaster(const ser4cpp::rseq_t &buffer) {
    context->OnReceive(opendnp3::Message(this->addresses.Reverse(), buffer));
    return exe->run_many();
  }

private:
  const opendnp3::Addresses addresses;

  const NullLogger logger;
  const std::shared_ptr<exe4cpp::MockExecutor> exe;
  const std::shared_ptr<MockMasterApplication> application;
  const std::shared_ptr<opendnp3::MContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ser4cpp::rseq_t buffer(Data, Size);

  opendnp3::MasterParams config;
  MasterTestObject t(config);

  opendnp3::OContext octx;
  opendnp3::ParsedRequest req;
  std::bad_array_new_length bad;

  opendnp3::StateSolicitedConfirmWait state;
  state.OnNewNonReadRequest(&bad, &octx, &req);

  return 0;
}