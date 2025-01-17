#include <opendnp3/logging/LogLevels.h>
#include <opendnp3/outstation/DefaultOutstationApplication.h>
#include <opendnp3/outstation/OutstationContext.h>
#include <opendnp3/outstation/OutstationStackConfig.h>

#include <exe4cpp/MockExecutor.h>

#include <dnp3mocks/MockLowerLayer.h>
#include <dnp3mocks/MockOutstationApplication.h>
#include <dnp3mocks/MockOutstationInformation.h>
#include <dnp3mocks/MockSOEHandler.h>

#include <fuzzer/FuzzedDataProvider.h>

class OutstationTestObject {
public:
  OutstationTestObject(const opendnp3::OutstationConfig &config, const opendnp3::DatabaseConfig &dbConfig) : logger(), exe(std::make_shared<exe4cpp::MockExecutor>()), lower(std::make_shared<MockLowerLayer>()), application(std::make_shared<MockOutstationApplication>()), information(std::make_shared<MockOutstationInformation>()), meas(std::make_shared<MockSOEHandler>()), context(opendnp3::OContext::Create(logger.get_logger(), exe, lower, application, information, meas, config, dbConfig)) { lower->SetUpperLayer(*context); }

  ~OutstationTestObject() {}

  size_t SendToOutstation(const ser4cpp::rseq_t &buffer) {
    context->OnReceive(opendnp3::Message(opendnp3::Addresses(), buffer));
    return exe->run_many();
  }

  size_t LowerLayerUp() {
    context->OnLowerLayerUp();
    return exe->run_many();
  }

private:
  const NullLogger logger;
  const std::shared_ptr<exe4cpp::MockExecutor> exe;
  const std::shared_ptr<MockLowerLayer> lower;
  const std::shared_ptr<MockOutstationApplication> application;
  const std::shared_ptr<MockOutstationInformation> information;
  const std::shared_ptr<MockSOEHandler> meas;
  const std::shared_ptr<opendnp3::OContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  opendnp3::OutstationConfig config;
  opendnp3::DatabaseConfig dbConfig;

  OutstationTestObject t(config, dbConfig);
  t.LowerLayerUp();

  if (stream.remaining_bytes() > 0) {
    ser4cpp::rseq_t buffer(stream.ConsumeRemainingBytes().data(), stream.remaining_bytes());
    t.SendToOutstation(buffer);
  }

  return 0;
}