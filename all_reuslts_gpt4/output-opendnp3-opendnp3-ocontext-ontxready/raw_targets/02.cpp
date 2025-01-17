#include <opendnp3/logging/LogLevels.h>
#include <opendnp3/outstation/DefaultOutstationApplication.h>

#include <exe4cpp/MockExecutor.h>

#include <dnp3mocks/MockLowerLayer.h>
#include <dnp3mocks/MockOutstationApplication.h>
#include <dnp3mocks/MockOutstationSOEHandler.h>

#include <outstation/OContext.h>

#include "NullLogHandler.h"

class OutstationTestObject {
public:
  OutstationTestObject(const opendnp3::OutstationConfig &config, const opendnp3::DatabaseConfig &dbConfig) : addresses(), logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), soe(std::make_shared<MockOutstationSOEHandler>()), lower(std::make_shared<MockLowerLayer>()), application(std::make_shared<MockOutstationApplication>()), context(opendnp3::OContext::Create(addresses, logger.get_logger(), exe, lower, soe, application, config, dbConfig)) { lower->SetUpperLayer(*context); }

  ~OutstationTestObject() { this->context->Shutdown(); }

  size_t SendToOutstation(const ser4cpp::rseq_t &buffer) {
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
  const std::shared_ptr<MockOutstationSOEHandler> soe;
  const std::shared_ptr<MockLowerLayer> lower;
  const std::shared_ptr<MockOutstationApplication> application;
  const std::shared_ptr<opendnp3::OContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ser4cpp::rseq_t buffer(Data, Size);

  opendnp3::OutstationConfig config;
  opendnp3::DatabaseConfig dbConfig;
  OutstationTestObject t(config, dbConfig);
  t.LowerLayerUp();
  t.SendToOutstation(buffer);
  t.context->OnTxReady();
  return 0;
}