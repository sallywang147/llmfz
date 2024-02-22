#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rebase.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct rebase_options options;
  options.verbose = provider.ConsumeBool();
  options.dry_run = provider.ConsumeBool();
  options.ignore_missing = provider.ConsumeBool();
  options.ignore_wrong_size = provider.ConsumeBool();
  options.ignore_wrong_type = provider.ConsumeBool();
  options.ignore_wrong_address = provider.ConsumeBool();
  options.ignore_wrong_path = provider.ConsumeBool();
  options.ignore_wrong_file_type = provider.ConsumeBool();
  options.ignore_wrong_file_size = provider.ConsumeBool();
  options.ignore_wrong_file_mtime = provider.ConsumeBool();
  options.ignore_wrong_file_ctime = provider.ConsumeBool();
  options.ignore_wrong_file_atime = provider.ConsumeBool();
  options.ignore_wrong_file_nlink = provider.ConsumeBool();
  options.ignore_wrong_file_uid = provider.ConsumeBool();
  options.ignore_wrong_file_gid = provider.ConsumeBool();
  options.ignore_wrong_file_mode = provider.ConsumeBool();
  options.ignore_wrong_file_rdev = provider.ConsumeBool();
  options.ignore_wrong_file_flags = provider.ConsumeBool();
  options.ignore_wrong_file_xattr = provider.ConsumeBool();
  options.ignore_wrong_file_acl = provider.ConsumeBool();
  options.ignore_wrong_file_selinux_context = provider.ConsumeBool();
  options.ignore_wrong_file_chattr = provider.ConsumeBool();
  options.ignore_wrong_file_link_target = provider.ConsumeBool();
  options.ignore_wrong_file_link_count = provider.ConsumeBool();
  options.ignore_wrong_file_socket_type = provider.ConsumeBool();
  options.ignore_wrong_file_socket_protocol = provider.ConsumeBool();
  options.ignore_wrong_file_socket_address = provider.ConsumeBool();
  options.ignore_wrong_file_socket_port = provider.ConsumeBool();
  options.ignore_wrong_file_socket_path = provider.ConsumeBool();
  options.ignore_wrong_file_socket_options = provider.ConsumeBool();
  options.ignore_wrong_file_socket_buffer_size = provider.ConsumeBool();
  options.ignore_wrong_file_socket_timeout = provider.ConsumeBool();
  options.ignore_wrong_file_socket_linger = provider.ConsumeBool();
  options.ignore_wrong_file_socket_reuseaddr = provider.ConsumeBool();
  options.ignore_wrong_file_socket_keepalive = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_nodelay = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_cork = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_window_size = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_max_segment_size = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_timestamps = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_sack = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_ecn = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_syncookies = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_time_wait_timeout = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fin_timeout = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_keepalive_time = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_keepalive_intvl = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_keepalive_probes = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_user_timeout = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_queue_size = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_connect = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_cookie = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_md5sig = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_cookie_reqd = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_loss = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_blackhole = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_timeout = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_interval = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_backoff = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_max_retries = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_initial_delay = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_max_delay = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_multiplier = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_base_delay = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_min_delay = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_max_delay_multiplier = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_base_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_min_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_max_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_min_max_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_min_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_min_max = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_max_min = provider.ConsumeBool();
  options.ignore_wrong_file_socket_tcp_fastopen_syn_rexmit_exponential_backoff_multiplier_max_max_max = provider.ConsumeBool();
  run_specific_rebase(&options);
  return 0;
}