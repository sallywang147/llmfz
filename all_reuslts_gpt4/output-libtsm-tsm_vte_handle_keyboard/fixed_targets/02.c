#include <fuzzer/FuzzedDataProvider.h>
#include <tsm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct tsm_vte *vte;
  struct tsm_screen *screen;
  struct tsm_vte_attr attr;

  screen = tsm_screen_new();
  if (!screen) {
    return 0;
  }

  vte = tsm_vte_new(screen, nullptr, nullptr, nullptr, nullptr);
  if (!vte) {
    tsm_screen_unref(screen);
    return 0;
  }

  int keysym = stream.ConsumeIntegral<int>();
  int ascii = stream.ConsumeIntegral<int>();
  int mods = stream.ConsumeIntegral<int>();
  int unicode = stream.ConsumeIntegral<int>();

  tsm_vte_handle_keyboard(vte, keysym, ascii, mods, unicode);

  tsm_vte_unref(vte);
  tsm_screen_unref(screen);

  return 0;
}