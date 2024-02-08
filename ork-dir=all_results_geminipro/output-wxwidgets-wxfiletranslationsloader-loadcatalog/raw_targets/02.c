#include "wx/app.h"
#include "wx/catalog.h"
#include "wx/file.h"
#include "wx/log.h"
#include "wx/mstream.h"

#if wxDEBUG_LEVEL

static void exitAssertHandler(const wxString &file, int line, const wxString &func, const wxString &cond, const wxString &msg);

static volatile wxAssertHandler_t origAssertHandler = wxSetAssertHandler(exitAssertHandler);

static void exitAssertHandler(const wxString &file, int line, const wxString &func, const wxString &cond, const wxString &msg) {
  origAssertHandler(file, line, func, cond, msg);

  exit(1);
}

#endif // wxDEBUG_LEVEL

extern "C" int LLVMFuzzerTestOneInput(const wxUint8 *data, size_t size) {
  wxLogNull noLog;

  wxFileTranslationsLoader loader;
  wxAppTraits traits;
  wxString domain, lang;

  wxMemoryInputStream mis(data, size);
  loader.LoadCatalog(&traits, &domain, &lang, &mis);

  return 0;
}