#include <opendnp3/outstation/OContext.h>
#include <opendnp3/logging/LogLevels.h>
#include <opendnp3/outstation/DefaultOutstationApplication.h>

#include <exe4cpp/MockExecutor.h>

#include <dnp3mocks/MockLowerLayer.h>
#include <dnp3mocks/MockOutstationApplication.h>
#include <dnp3mocks/MockSOEHandler.h>

#include <outstation/OutstationContext.h>
#include <outstation/OutstationSchedulerBackend.h>

#include "NullLogHandler.h"

class OutstationTestObject {
public:
  OutstationTestObject(const opendnp3::OutstationParams &params) : addresses(), logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), meas(std::make_shared<MockSOEHandler>()), lower(std::make_shared<MockLowerLayer>()), application(std::make_shared<MockOutstationApplication>()), scheduler(std::make_shared<opendnp3::OutstationSchedulerBackend>(exe)), context(opendnp3::OContext::Create(addresses, logger.get_logger(), exe, lower, meas, application, this->scheduler, params)) { lower->SetUpperLayer(*context); }

  ~OutstationTestObject() { this->scheduler->Shutdown(); }

  size_t SendToOutstation(const ser4cpp::rseq_t &buffer) {
    context->OnReceive(opendnp3::Message(this->addresses.Reverse(), buffer));
    return exe->run_many();
  }

  size_t LowerLayerUp() {
    context->OnLowerLayerUp();
    return exe->run_many();
  }

  bool OnTxReady() { return context->OnTxReady(context.get()); }

private:
  const opendnp3::Addresses addresses;

  const NullLogger logger;
  const std::shared_ptr<exe4cpp::MockExecutor> exe;
  const std::shared_ptr<MockSOEHandler> meas;
  const std::shared_ptr<MockLowerLayer> lower;
  const std::shared_ptr<MockOutstationApplication> application;
  const std::shared_ptr<opendnp3::IOutstationScheduler> scheduler;
  const std::shared_ptr<opendnp3::OContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ser4cpp::rseq_t buffer(Data, Size);

  opendnp3::OutstationParams config;
  OutstationTestObject t(config);
  t.LowerLayerUp();
  t.SendToOutstation(buffer);
  t.OnTxReady();
  return 0;
}