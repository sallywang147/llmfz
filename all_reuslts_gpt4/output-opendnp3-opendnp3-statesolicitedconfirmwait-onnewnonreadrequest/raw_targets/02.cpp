#include <opendnp3/logging/LogLevels.h>
#include <opendnp3/master/DefaultMasterApplication.h>

#include <exe4cpp/MockExecutor.h>

#include <dnp3mocks/MockLowerLayer.h>
#include <dnp3mocks/MockMasterApplication.h>
#include <dnp3mocks/MockSOEHandler.h>

#include <master/MasterContext.h>
#include <master/MasterSchedulerBackend.h>

#include "NullLogHandler.h"
#include "fuzzer/FuzzedDataProvider.h"

class MasterTestObject {
public:
  MasterTestObject(const opendnp3::MasterParams &params) : addresses(), logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), meas(std::make_shared<MockSOEHandler>()), lower(std::make_shared<MockLowerLayer>()), application(std::make_shared<MockMasterApplication>()), scheduler(std::make_shared<opendnp3::MasterSchedulerBackend>(exe)), context(opendnp3::MContext::Create(addresses, logger.get_logger(), exe, lower, meas, application, this->scheduler, params)) { lower->SetUpperLayer(*context); }

  ~MasterTestObject() { this->scheduler->Shutdown(); }

  size_t SendToMaster(const ser4cpp::rseq_t &buffer) {
    context->OnReceive(opendnp3::Message(this->addresses.Reverse(), buffer));
    return exe->run_many();
  }

  size_t LowerLayerUp() {
    context->OnLowerLayerUp();
    return exe->run_many();
  }

private:
  const opendnp3::Addresses addresses;

  const NullLogger logger;
  const std::shared_ptr<exe4cpp::MockExecutor> exe;
  const std::shared_ptr<MockSOEHandler> meas;
  const std::shared_ptr<MockLowerLayer> lower;
  const std::shared_ptr<MockMasterApplication> application;
  const std::shared_ptr<opendnp3::IMasterScheduler> scheduler;
  const std::shared_ptr<opendnp3::MContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  opendnp3::MasterParams config;
  MasterTestObject t(config);
  t.LowerLayerUp();

  std::bad_array_new_length bad_array_new_length;
  opendnp3::OContext oContext;
  opendnp3::ParsedRequest parsedRequest;

  opendnp3::StateSolicitedConfirmWait stateSolicitedConfirmWait;
  stateSolicitedConfirmWait.OnNewNonReadRequest(&bad_array_new_length, &oContext, &parsedRequest);

  return 0;
}