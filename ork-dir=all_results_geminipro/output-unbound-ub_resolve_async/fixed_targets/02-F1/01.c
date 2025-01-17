#include "unbound.h"
#include "util/data/msgreply.h"
#include "util/data/packed_rrset.h"
#include "util/regional.h"
#include "util/config_file.h"
#include "util/log.h"
#include "util/net_help.h"
#include "util/module.h"
#include "util/random.h"
#include "util/rtt.h"
#include "util/storage/slabhash.h"
#include "util/tube.h"
#include "util/ub_event.h"
#include "util/ub_json.h"
#include "util/ub_msg.h"
#include "util/ub_modlog.h"
#include "util/ub_port.h"
#include "util/ub_socks.h"
#include "util/ub_thread.h"
#include "util/version.h"

extern "C" {
int ub_resolve_async(struct ub_ctx * ctx, char * name, int rrtype, int rrclass, char * mydata, func_type * callback, int * async_id);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct ub_ctx *ctx = NULL;
  char *name = NULL;
  int rrtype = 0;
  int rrclass = 0;
  char *mydata = NULL;
  func_type *callback = NULL;
  int *async_id = NULL;
  struct config_file *cfg = NULL;
  struct regional *region = NULL;
  struct slabhash *slab = NULL;
  struct rtt_info *rttinfo = NULL;
  struct ub_eventbase *base = NULL;
  struct ub_thread *thr = NULL;
  struct sockaddr_storage addr;
  socklen_t addrlen;
  struct sockaddr_storage addr2;
  socklen_t addrlen2;
  struct timeval now;
  struct config_stub *cfg_stub = NULL;
  struct config_stub *cfg_stub2 = NULL;
  struct config_stub *cfg_stub3 = NULL;
  struct config_stub *cfg_stub4 = NULL;
  struct config_stub *cfg_stub5 = NULL;
  struct config_stub *cfg_stub6 = NULL;
  struct config_stub *cfg_stub7 = NULL;
  struct config_stub *cfg_stub8 = NULL;
  struct config_stub *cfg_stub9 = NULL;
  struct config_stub *cfg_stub10 = NULL;
  struct config_stub *cfg_stub11 = NULL;
  struct config_stub *cfg_stub12 = NULL;
  struct config_stub *cfg_stub13 = NULL;
  struct config_stub *cfg_stub14 = NULL;
  struct config_stub *cfg_stub15 = NULL;
  struct config_stub *cfg_stub16 = NULL;
  struct config_stub *cfg_stub17 = NULL;
  struct config_stub *cfg_stub18 = NULL;
  struct config_stub *cfg_stub19 = NULL;
  struct config_stub *cfg_stub20 = NULL;
  struct config_stub *cfg_stub21 = NULL;
  struct config_stub *cfg_stub22 = NULL;
  struct config_stub *cfg_stub23 = NULL;
  struct config_stub *cfg_stub24 = NULL;
  struct config_stub *cfg_stub25 = NULL;
  struct config_stub *cfg_stub26 = NULL;
  struct config_stub *cfg_stub27 = NULL;
  struct config_stub *cfg_stub28 = NULL;
  struct config_stub *cfg_stub29 = NULL;
  struct config_stub *cfg_stub30 = NULL;
  struct config_stub *cfg_stub31 = NULL;
  struct config_stub *cfg_stub32 = NULL;
  struct config_stub *cfg_stub33 = NULL;
  struct config_stub *cfg_stub34 = NULL;
  struct config_stub *cfg_stub35 = NULL;
  struct config_stub *cfg_stub36 = NULL;
  struct config_stub *cfg_stub37 = NULL;
  struct config_stub *cfg_stub38 = NULL;
  struct config_stub *cfg_stub39 = NULL;
  struct config_stub *cfg_stub40 = NULL;
  struct config_stub *cfg_stub41 = NULL;
  struct config_stub *cfg_stub42 = NULL;
  struct config_stub *cfg_stub43 = NULL;
  struct config_stub *cfg_stub44 = NULL;
  struct config_stub *cfg_stub45 = NULL;
  struct config_stub *cfg_stub46 = NULL;
  struct config_stub *cfg_stub47 = NULL;
  struct config_stub *cfg_stub48 = NULL;
  struct config_stub *cfg_stub49 = NULL;
  struct config_stub *cfg_stub50 = NULL;
  struct config_stub *cfg_stub51 = NULL;
  struct config_stub *cfg_stub52 = NULL;
  struct config_stub *cfg_stub53 = NULL;
  struct config_stub *cfg_stub54 = NULL;
  struct config_stub *cfg_stub55 = NULL;
  struct config_stub *cfg_stub56 = NULL;
  struct config_stub *cfg_stub57 = NULL;
  struct config_stub *cfg_stub58 = NULL;
  struct config_stub *cfg_stub59 = NULL;
  struct config_stub *cfg_stub60 = NULL;
  struct config_stub *cfg_stub61 = NULL;
  struct config_stub *cfg_stub62 = NULL;
  struct config_stub *cfg_stub63 = NULL;
  struct config_stub *cfg_stub64 = NULL;
  struct config_stub *cfg_stub65 = NULL;
  struct config_stub *cfg_stub66 = NULL;
  struct config_stub *cfg_stub67 = NULL;
  struct config_stub *cfg_stub68 = NULL;
  struct config_stub *cfg_stub69 = NULL;
  struct config_stub *cfg_stub70 = NULL;
  struct config_stub *cfg_stub71 = NULL;
  struct config_stub *cfg_stub72 = NULL;
  struct config_stub *cfg_stub73 = NULL;
  struct config_stub *cfg_stub74 = NULL;
  struct config_stub *cfg_stub75 = NULL;
  struct config_stub *cfg_stub76 = NULL;
  struct config_stub *cfg_stub77 = NULL;
  struct config_stub *cfg_stub78 = NULL;
  struct config_stub *cfg_stub79 = NULL;
  struct config_stub *cfg_stub80 = NULL;
  struct config_stub *cfg_stub81 = NULL;
  struct config_stub *cfg_stub82 = NULL;
  struct config_stub *cfg_stub83 = NULL;
  struct config_stub *cfg_stub84 = NULL;
  struct config_stub *cfg_stub85 = NULL;
  struct config_stub *cfg_stub86 = NULL;
  struct config_stub *cfg_stub87 = NULL;
  struct config_stub *cfg_stub88 = NULL;
  struct config_stub *cfg_stub89 = NULL;
  struct config_stub *cfg_stub90 = NULL;
  struct config_stub *cfg_stub91 = NULL;
  struct config_stub *cfg_stub92 = NULL;
  struct config_stub *cfg_stub93 = NULL;
  struct config_stub *cfg_stub94 = NULL;
  struct config_stub *cfg_stub95 = NULL;
  struct config_stub *cfg_stub96 = NULL;
  struct config_stub *cfg_stub97 = NULL;
  struct config_stub *cfg_stub98 = NULL;
  struct config_stub *cfg_stub99 = NULL;
  struct config_stub *cfg_stub100 = NULL;
  struct config_stub *cfg_stub101 = NULL;
  struct config_stub *cfg_stub102 = NULL;
  struct config_stub *cfg_stub103 = NULL;
  struct config_stub *cfg_stub104 = NULL;
  struct config_stub *cfg_stub1