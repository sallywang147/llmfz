#include <opendnp3/logging/LogLevels.h>
#include <opendnp3/outstation/DefaultOutstationApplication.h>

#include <exe4cpp/MockExecutor.h>

#include <dnp3mocks/MockLowerLayer.h>
#include <dnp3mocks/MockOutstationApplication.h>
#include <dnp3mocks/MockSOEHandler.h>

#include <outstation/OutstationContext.h>
#include <outstation/OutstationSchedulerBackend.h>

#include "NullLogHandler.h"

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

class OutstationTestObject {
public:
  OutstationTestObject() : addresses(), logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), meas(std::make_shared<MockSOEHandler>()), lower(std::make_shared<MockLowerLayer>()), application(std::make_shared<MockOutstationApplication>()), scheduler(std::make_shared<opendnp3::OutstationSchedulerBackend>(exe)), context(opendnp3::OContext::Create(addresses, logger.get_logger(), exe, lower, meas, application, this->scheduler)) { lower->SetUpperLayer(*context); }

  ~OutstationTestObject() { this->scheduler->Shutdown(); }

  size_t SendToOutstation(const ser4cpp::rseq_t &buffer) {
    context->OnReceive(opendnp3::Message(this->addresses.Reverse(), buffer));
    return exe->run_many();
  }

  size_t LowerLayerUp() {
    context->OnLowerLayerUp();
    return exe->run_many();
  }

  bool OnTxReady(opendnp3::OContext *context) {
    return context->OnTxReady(context);
  }

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
  FuzzedDataProvider dataProvider(Data, Size);
  ser4cpp::rseq_t buffer = dataProvider.ConsumeRemainingBytes<uint8_t>();

  OutstationTestObject t;
  t.LowerLayerUp();
  t.SendToOutstation(buffer);
  t.OnTxReady(t.context.get());
  return 0;
}