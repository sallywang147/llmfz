#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "libunbound/unbound.h"

extern "C" {
#include "libunbound/config.h"
#include "libunbound/context.h"
#include "libunbound/libunbound.h"
#include "libunbound/options.h"
#include "libunbound/unbound.h"
}

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct ub_ctx* ctx = NULL;
  struct ub_result* result = NULL;
  struct ub_version* ver = NULL;
  struct ub_stats* stats = NULL;
  struct ub_option* opt = NULL;
  struct ub_msg* msg = NULL;
  struct ub_rbtree* tree = NULL;
  struct ub_cache* cache = NULL;
  struct ub_symtab* symtab = NULL;
  struct ub_sock* sock = NULL;
  struct ub_serv* serv = NULL;
  struct ub_rotor* rotor = NULL;
  struct ub_stats_info* stats_info = NULL;
  struct ub_stats_key* stats_key = NULL;
  struct ub_stats_bucket* stats_bucket = NULL;
  struct ub_stats_module* stats_module = NULL;
  struct ub_stats_zone* stats_zone = NULL;
  struct ub_stats_client* stats_client = NULL;
  struct ub_stats_query* stats_query = NULL;
  struct ub_stats_thread* stats_thread = NULL;
  struct ub_stats_timer* stats_timer = NULL;
  struct ub_stats_mem* stats_mem = NULL;
  struct ub_stats_msg* stats_msg = NULL;
  struct ub_stats_resolver* stats_resolver = NULL;
  struct ub_stats_infra* stats_infra = NULL;
  struct ub_stats_fwd* stats_fwd = NULL;
  struct ub_stats_http* stats_http = NULL;
  struct ub_stats_tsig* stats_tsig = NULL;
  struct ub_stats_dnssec* stats_dnssec = NULL;
  struct ub_stats_stub* stats_stub = NULL;
  struct ub_stats_val* stats_val = NULL;
  struct ub_stats_child* stats_child = NULL;
  struct ub_stats_rrset* stats_rrset = NULL;
  struct ub_stats_msg_cache* stats_msg_cache = NULL;
  struct ub_stats_dns64* stats_dns64 = NULL;
  struct ub_stats_ext_state* stats_ext_state = NULL;
  struct ub_stats_ext_client* stats_ext_client = NULL;
  struct ub_stats_ext_query* stats_ext_query = NULL;
  struct ub_stats_ext_thread* stats_ext_thread = NULL;
  struct ub_stats_ext_timer* stats_ext_timer = NULL;
  struct ub_stats_ext_mem* stats_ext_mem = NULL;
  struct ub_stats_ext_msg* stats_ext_msg = NULL;
  struct ub_stats_ext_resolver* stats_ext_resolver = NULL;
  struct ub_stats_ext_infra* stats_ext_infra = NULL;
  struct ub_stats_ext_fwd* stats_ext_fwd = NULL;
  struct ub_stats_ext_http* stats_ext_http = NULL;
  struct ub_stats_ext_tsig* stats_ext_tsig = NULL;
  struct ub_stats_ext_dnssec* stats_ext_dnssec = NULL;
  struct ub_stats_ext_stub* stats_ext_stub = NULL;
  struct ub_stats_ext_val* stats_ext_val = NULL;
  struct ub_stats_ext_child* stats_ext_child = NULL;
  struct ub_stats_ext_rrset* stats_ext_rrset = NULL;
  struct ub_stats_ext_msg_cache* stats_ext_msg_cache = NULL;
  struct ub_stats_ext_dns64* stats_ext_dns64 = NULL;
  struct ub_stats_ext_ratelim* stats_ext_ratelim = NULL;
  struct ub_stats_ext_rpz* stats_ext_rpz = NULL;
  struct ub_stats_ext_dlv* stats_ext_dlv = NULL;
  struct ub_stats_ext_svc* stats_ext_svc = NULL;
  struct ub_stats_ext_infra_msg* stats_ext_infra_msg = NULL;
  struct ub_stats_ext_infra_rrset* stats_ext_infra_rrset = NULL;
  struct ub_stats_ext_infra_thread* stats_ext_infra_thread = NULL;
  struct ub_stats_ext_infra_timer* stats_ext_infra_timer = NULL;
  struct ub_stats_ext_infra_mem* stats_ext_infra_mem = NULL;
  struct ub_stats_ext_infra_resolver* stats_ext_infra_resolver = NULL;
  struct ub_stats_ext_infra_fwd* stats_ext_infra_fwd = NULL;
  struct ub_stats_ext_infra_http* stats_ext_infra_http = NULL;
  struct ub_stats_ext_infra_tsig* stats_ext_infra_tsig = NULL;
  struct ub_stats_ext_infra_dnssec* stats_ext_infra_dnssec = NULL;
  struct ub_stats_ext_infra_stub* stats_ext_infra_stub = NULL;
  struct ub_stats_ext_infra_val* stats_ext_infra_val = NULL;
  struct ub_stats_ext_infra_child* stats_ext_infra_child = NULL;
  struct ub_stats_ext_infra_rrset* stats_ext_infra_rrset = NULL;
  struct ub_stats_ext_infra_msg_cache* stats_ext_infra_msg_cache = NULL;
  struct ub_stats_ext_infra_dns64* stats_ext_infra_dns64 = NULL;
  struct ub_stats_ext_infra_ratelim* stats_ext_infra_ratelim = NULL;
  struct ub_stats_ext_infra_rpz* stats_ext_infra_rpz = NULL;
  struct ub_stats_ext_infra_dlv* stats_ext_infra_dlv = NULL;
  struct ub_stats_ext_infra_svc* stats_ext_infra_svc = NULL;
  struct ub_stats_ext_infra_msg_cache_lru* stats_ext_infra_msg_cache_lru = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_size*
      stats_ext_infra_msg_cache_lru_size = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_time*
      stats_ext_infra_msg_cache_lru_time = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_neg*
      stats_ext_infra_msg_cache_lru_neg = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_pos*
      stats_ext_infra_msg_cache_lru_pos = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_rrset*
      stats_ext_infra_msg_cache_lru_rrset = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_rrset_size*
      stats_ext_infra_msg_cache_lru_rrset_size = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_rrset_time*
      stats_ext_infra_msg_cache_lru_rrset_time = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_rrset_neg*
      stats_ext_infra_msg_cache_lru_rrset_neg = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_rrset_pos*
      stats_ext_infra_msg_cache_lru_rrset_pos = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_neg_size*
      stats_ext_infra_msg_cache_lru_neg_size = NULL;
  struct ub_stats_ext_infra_msg_cache_lru_neg_time*
      stats_ext_infra_msg_cache_lru_neg_time = NULL;