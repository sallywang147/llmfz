#include <fuzzer/FuzzedDataProvider.h>
#include <lib/settings.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct private_settings_t *this = new struct private_settings_t;
  size_t len = stream.ConsumeIntegralInRange(0, 1024);
  std::vector<uint8_t> pattern = stream.ConsumeBytes<uint8_t>(len);
  bool merge = stream.ConsumeBool();
  len = stream.ConsumeIntegralInRange(0, 1024);
  std::vector<uint8_t> key = stream.ConsumeBytes<uint8_t>(len);
  bool ret = load_files_section(this, (char*)pattern.data(), merge, (char*)key.data());
  delete this;
  return 0;
}