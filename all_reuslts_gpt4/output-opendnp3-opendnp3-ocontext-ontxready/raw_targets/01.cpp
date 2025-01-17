#include <opendnp3/outstation/OutstationContext.h>
#include <fuzzer/FuzzedDataProvider.h>

class OutstationTestObject {
public:
  OutstationTestObject() : context(std::make_shared<opendnp3::OContext>()) {}

  bool CallOnTxReady() {
    return context->OnTxReady();
  }

private:
  std::shared_ptr<opendnp3::OContext> context;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  OutstationTestObject testObject;
  bool result = testObject.CallOnTxReady();

  return 0;
}