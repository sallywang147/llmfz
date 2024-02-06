#include <fuzzer/FuzzedDataProvider.h>
#include <dpif/dpif.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <dpif/dpif.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t name_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* name = new char[name_size + 1];
  stream.ConsumeBytes(name, name_size);
  name[name_size] = '\0';

  dpif_3273* dpif = new dpif_3273();
  dp_netdev** dpp = new dp_netdev*[1]; // Fix the initialization of dpp

  int result = create_dp_netdev(name, dpif, dpp);
  delete[] name;
  delete dpif;
  delete[] dpp;

  return result;
}