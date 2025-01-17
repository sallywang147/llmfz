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

  ub_ctx_create(&ctx, 0);
  ub_ctx_set_option(ctx, UB_OPT_MESSAGE_CACHE_SIZE, 1024);
  ub_ctx_set_option(ctx, UB_OPT_MAX_UDP_SIZE, 512);
  ub_ctx_set_option(ctx, UB_OPT_MAX_TCP_SIZE, 65536);
  ub_ctx_set_option(ctx, UB_OPT_TIMEOUT, 1000);
  ub_ctx_set_option(ctx, UB_OPT_TCP_IDLE_TIMEOUT, 120);
  ub_ctx_set_option(ctx, UB_OPT_KEEPALIVE_TIMEOUT, 30);
  ub_ctx_set_option(ctx, UB_OPT_SO_RCVBUF, 16384);
  ub_ctx_set_option(ctx, UB_OPT_SO_SNDBUF, 16384);
  ub_ctx_set_option(ctx, UB_OPT_NUM_THREADS, 1);
  ub_ctx_set_option(ctx, UB_OPT_THREAD_MIN_TTL, 10);
  ub_ctx_set_option(ctx, UB_OPT_THREAD_MAX_TTL, 60);
  ub_ctx_set_option(ctx, UB_OPT_LOG_VERBOSITY, 0);
  ub_ctx_set_option(ctx, UB_OPT_LOG_SYSLOG, 0);
  ub_ctx_set_option(ctx, UB_OPT_LOG_FILE, NULL);
  ub_ctx_set_option(ctx, UB_OPT_LOG_LEVEL, 0);
  ub_ctx_set_option(ctx, UB_OPT_LOG_IDENT, "unbound");
  ub_ctx_set_option(ctx, UB_OPT_LOCAL_ZONE, NULL);
  ub_ctx_set_option(ctx, UB_OPT_LOCAL_DATA, NULL);
  ub_ctx_set_option(ctx, UB_OPT_TRUST_ANCHOR_FILE, NULL);
  ub_ctx_set_option(ctx, UB_OPT_ROOT_HINTS, NULL);
  ub_ctx_set_option(ctx, UB_OPT_PRIVATE_KEY, NULL);
  ub_ctx_set_option(ctx, UB_OPT_PRIVATE_KEY_FILE, NULL);
  ub_ctx_set_option(ctx, UB_OPT_PRIVATE_KEY_PASSWD, NULL);
  ub_ctx_set_option(ctx, UB_OPT_HOST_KEY_FILE, NULL);
  ub_ctx_set_option(ctx, UB_OPT_HOST_KEY_PASSWD, NULL);
  ub_ctx_set_option(ctx, UB_OPT_CONTROL_PORT, 0);
  ub_ctx_set_option(ctx, UB_OPT_CONTROL_INTERFACE, "127.0.0.1");
  ub_ctx_set_option(ctx, UB_OPT_DO_IP4, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_IP6, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_UDP, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_TCP, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_FILE, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_MEMSTATS, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_VALGRIND, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_CACHE_FLUSH, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_DNSSEC, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_DNSSEC_AUTH, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_DNSSEC_NOAUTH, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_DNSSEC_NSEC3_SHA1, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_DNSSEC_NSEC3_HMACSHA1, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPSEC, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_TCP_KEEPALIVE, 1);
  ub_ctx_set_option(ctx, UB_OPT_DO_TCP_FASTOPEN, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV4_RECVPOLICY, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_RECVPOLICY, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_V6ONLY, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_RTHDR, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_ADDR_SELECT, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_USE_ZONE, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_AAAA_FLAG_NODATA, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_AAAA_FLAG_DNSSEC, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IPV6_AAAA_NEGATIVE, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IP_TRANSPARENT, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IP_TRANSPARENT_FORWARD, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IP_TRANSPARENT_REVERSE, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_IP_TRANSPARENT_USE_EDNS0, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_CLIENT_SUBNET, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_CLIENT_SUBNET_REVERSE, 0);
  ub_ctx_set_option(ctx, UB_OPT_DO_USE_EDNS0, 1);
  ub_ctx_set_option(ctx