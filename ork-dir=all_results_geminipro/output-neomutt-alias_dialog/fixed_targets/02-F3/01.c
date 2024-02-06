#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "config/lib.h"
#include "core/lib.h"
#include "email/lib.h"
#include "globals.h"
#include "init.h"
#include "mutt/lib.h"
#include "mutt_curses.h"
#include "mutt_dialog.h"
#include "mutt_menu.h"
#include "mutt_txt.h"
#include "mutt_win.h"
#include "parse.h"
#include "sort.h"

extern "C" {
#include "mutt_recurse.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  MuttLogger = log_disp_null;
  struct ConfigSet *cs = cs_new(16);
  NeoMutt = neomutt_new(cs);
  init_config(cs);
  OptNoCurses = true;
  struct Mailbox *mb = mailbox_new();
  struct ConfigSubset *subset = config_subset_new(cs, "alias");
  alias_dialog(mb, subset);
  config_subset_free(&subset);
  mailbox_free(&mb);
  neomutt_free(&NeoMutt);
  cs_free(&cs);
  return 0;
}