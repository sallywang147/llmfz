#include <fuzzer/FuzzedDataProvider.h>
#include <znc/ZNCString.h>
#include <znc/ZNC.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  CString sConfigFile = stream.ConsumeRandomLengthString().c_str();
  CString sError = stream.ConsumeRandomLengthString().c_str();

  CZNC znc;
  znc.ParseConfig(&znc, &sConfigFile, &sError);

  return 0;
}