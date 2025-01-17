#include <fuzzer/FuzzedDataProvider.h>
#include "libtsm.h"

// Entry point for LibFuzzer.
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct tsm_screen *screen;
  struct tsm_vte *vte;
  const int scrollback_size = 200; // frecon use 200

  tsm_screen_new(&screen, NULL, NULL);
  tsm_screen_set_max_sb(screen, scrollback_size);
  tsm_vte_new(&vte, screen, NULL, NULL, NULL, NULL);
  tsm_screen_resize(screen, 80, 24);

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    int keysym = provider.ConsumeIntegral<int>();
    int ascii = provider.ConsumeIntegral<int>();
    int mods = provider.ConsumeIntegral<int>();
    int unicode = provider.ConsumeIntegral<int>();
    tsm_vte_handle_keyboard(vte, keysym, ascii, mods, unicode);
  }

  tsm_vte_unref(vte);
  tsm_screen_unref(screen);
  return 0;
}