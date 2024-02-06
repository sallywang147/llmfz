#include "fuzzer/FuzzedDataProvider.h"
#include "wx/apptrait.h"
#include "wx/intl.h"
#include "wx/msgout.h"
#include "wx/stdpaths.h"
#include "wx/xlocale.h"
#include "wx/translation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string domain = stream.ConsumeRandomLengthString();
  std::string lang = stream.ConsumeRandomLengthString();

  wxFileTranslationsLoader loader;
  wxAppTraits app_traits;
  wxLocale locale;

  locale.Init(lang.c_str(), domain.c_str());
  wxTranslations::Set(loader.LoadCatalog(&app_traits, &domain, &lang));

  return 0;
}