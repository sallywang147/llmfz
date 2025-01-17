#include <fuzzer/FuzzedDataProvider.h>
#include "wx/intl.h"
#include "wx/apptraits.h"
#include "wx/filetranslationsloader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  wxString domain = stream.ConsumeRandomLengthString();
  wxString lang = stream.ConsumeRandomLengthString();

  wxAppTraits appTraits;
  wxFileTranslationsLoader fileTranslationsLoader;
  wxMsgCatalog* catalog = fileTranslationsLoader.LoadCatalog(&appTraits, &domain, &lang);

  delete catalog;

  return 0;
}