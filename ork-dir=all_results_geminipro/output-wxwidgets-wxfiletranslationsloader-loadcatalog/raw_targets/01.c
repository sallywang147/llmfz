#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "wx/apptrait.h"
#include "wx/intl.h"
#include "wx/log.h"
#include "wx/mstream.h"
#include "wx/translation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    wxInitialize();
    initialized = true;
  }

  wxLogNull noLog;

  FuzzedDataProvider stream(data, size);
  std::string domain = stream.ConsumeRemainingBytesAsString();
  std::string lang = stream.ConsumeRemainingBytesAsString();

  wxFileTranslationsLoader loader;
  wxMsgCatalog* catalog = loader.LoadCatalog(nullptr, &domain, &lang);
  if (catalog) {
    delete catalog;
  }

  return 0;
}