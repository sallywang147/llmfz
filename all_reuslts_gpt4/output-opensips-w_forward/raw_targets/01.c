#include <assert.h>

#include "../parser/sdp/sdp.h"

#include "../cachedb/test/test_cachedb.h"
#include "../lib/test/test_csv.h"
#include "../mem/test/test_malloc.h"
#include "../str.h"

#include "../cmds.h"
#include "../dprint.h"
#include "../globals.h"
#include "../lib/list.h"
#include "../msg_translator.h"
#include "../socket_info.h"
#include "../sr_module.h"
#include "../sr_module_deps.h"

#include "../test/fuzz/fuzz_standalone.h"

static pv_spec_p pv_specs;
static int nspecs;

__attribute__((constructor)) void pv_specs_fuzz_init() {
  for (int i = 0; _pv_names_table[i].name.s != NULL; i++) {
    char namebuf[32];
    str name = {.s = namebuf};
    pv_specs = realloc(pv_specs, sizeof(pv_specs[0]) * (nspecs + 1));
    assert(pv_specs != NULL);
    name.len = sprintf(name.s, "$%s", _pv_names_table[i].name.s);
    if (pv_parse_spec(&name, &(pv_specs[nspecs])) == NULL)
      continue;
    pv_specs[nspecs].pvp.pvn.type = PV_NAME_PVAR;
    pv_specs[nspecs].pvp.pvn.u.dname = (void *)&pv_specs[nspecs];
    nspecs += 1;
  }
}

static const int count_noparam_cmds() {
  int r = 0;

  for (int i = 0; core_cmds[i].name != NULL; i++) {
    if (core_cmds[i].params[0].flags == 0)
      r += 1;
  }
  return (r);
}

const cmd_export_t *pick_some_command(uint8_t datap) {
  const int ncmds = count_noparam_cmds();
  int i, r, idx = datap % (ncmds + 1);

  if (idx == ncmds)
    return (0);
  for (i = r = 0; core_cmds[i].name != NULL; i++) {
    if (core_cmds[i].params[0].flags != 0)
      continue;
    if (r == idx)
      return &core_cmds[i];
    r += 1;
  }
  abort();
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  str buf;
  const int ncmds = count_noparam_cmds();
  struct socket_info si = {};

  if (size <= ncmds + 1) {
    return 0;
  }

  struct sip_msg msg = {};
  msg.buf = (char *)data;
  msg.len = size - ncmds;

  if (parse_msg(msg.buf, msg.len, &msg) != 0)
    goto out;
  if (msg.via1 == NULL || msg.via1->error != PARSE_OK)
    goto out;
  msg.rcv.src_ip.af = AF_INET;
  msg.rcv.src_port = (unsigned short)66666;
  for (int i = 0; i < ncmds; i++) {
    const cmd_export_t *cmd = pick_some_command(data[size - ncmds + i]);
    if (cmd == NULL)
      continue;
    cmd->function(&msg, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  }
  for (int i = 0; i < nspecs; i++) {
    pv_value_t v = {};

    pv_specs[i].getf(&msg, &pv_specs[i].pvp, &v);
  }
  struct proxy_l dest = {};
  w_forward(&msg, &dest);
out:
  free_sip_msg(&msg);
  return 0;
}