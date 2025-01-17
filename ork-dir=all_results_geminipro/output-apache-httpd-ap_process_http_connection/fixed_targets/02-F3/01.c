#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "ap_config.h"
#include "ap_mmn.h"
#include "ap_mpm.h"
#include "httpd.h"
#include "http_config.h"
#include "http_connection.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_vhost.h"
#include "mod_core.h"
#include "scoreboard.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string server_root = stream.ConsumeRemainingBytesAsString();
  ap_init_scoreboard();
  ap_create_sb_handle();
  ap_global_pool = ap_make_sub_pool(NULL);
  ap_process_list = ap_make_list(ap_global_pool, 10);
  ap_scoreboard_image->global_pool = ap_global_pool;
  ap_scoreboard_image->process_list = ap_process_list;
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &ap_threads_limit);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_DAEMONS, &ap_daemons_limit);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_CONNECTIONS, &ap_max_connections);
  ap_mpm_query(AP_MPMQ_MAX_THREADS, &ap_threads_per_child);
  ap_mpm_query(AP_MPMQ_MAX_DAEMONS, &ap_daemons_to_start);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_THREADS, &ap_spare_threads);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_DAEMONS, &ap_spare_daemons);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_THREADS, &ap_min_spare_threads);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_DAEMONS, &ap_min_spare_daemons);
  ap_mpm_query(AP_MPMQ_MAX_REQUESTS_PER_CHILD, &ap_max_requests_per_child);
  ap_mpm_query(AP_MPMQ_MAX_MEM_FREE, &ap_max_mem_free);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_MEM_FREE, &ap_hard_limit_mem_free);
  ap_mpm_query(AP_MPMQ_CHILD_EXIT_STATUS, &ap_child_exit_status);
  ap_mpm_query(AP_MPMQ_STOPPING, &ap_mpm_stopping);
  ap_mpm_query(AP_MPMQ_RECLAIMING, &ap_reclaiming);
  ap_mpm_query(AP_MPMQ_VOLATILE, &ap_mpm_volatile);
  ap_mpm_query(AP_MPMQ_GENERATION, &ap_generation);
  ap_mpm_query(AP_MPMQ_MAX_GENERATION, &ap_max_generation);
  ap_mpm_query(AP_MPMQ_RESTART_TIME, &ap_restart_time);
  ap_mpm_query(AP_MPMQ_LRU_PID, &ap_lru_pid);
  ap_mpm_query(AP_MPMQ_LRU_STOPPED, &ap_lru_stopped);
  ap_mpm_query(AP_MPMQ_HARD_TIMEOUT, &ap_hard_timeout);
  ap_mpm_query(AP_MPMQ_KEEPALIVE_TIMEOUT, &ap_keepalive_timeout);
  ap_mpm_query(AP_MPMQ_SEND_TIMEOUT, &ap_send_timeout);
  ap_mpm_query(AP_MPMQ_LINGER_TIMEOUT, &ap_linger_timeout);
  ap_mpm_query(AP_MPMQ_MAX_WORKER_THREADS, &ap_max_worker_threads);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_WORKER_THREADS, &ap_max_spare_worker_threads);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_WORKER_THREADS, &ap_min_spare_worker_threads);
  ap_mpm_query(AP_MPMQ_MAX_THREADS_PER_CHILD, &ap_max_threads_per_child);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_THREADS_PER_CHILD, &ap_max_spare_threads_per_child);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_THREADS_PER_CHILD, &ap_min_spare_threads_per_child);
  ap_mpm_query(AP_MPMQ_MAX_REQUESTS_PER_THREAD, &ap_max_requests_per_thread);
  ap_mpm_query(AP_MPMQ_MAX_MEM_PER_CHILD, &ap_max_mem_per_child);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_MEM_PER_CHILD, &ap_hard_limit_mem_per_child);
  ap_mpm_query(AP_MPMQ_THREAD_LIMIT, &ap_thread_limit);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_THREADS, &ap_hard_limit_threads);
  ap_mpm_query(AP_MPMQ_DAEMON_LIMIT, &ap_daemons_limit);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_DAEMONS, &ap_hard_limit_daemons);
  ap_mpm_query(AP_MPMQ_CONNECTION_LIMIT, &ap_max_connections);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_CONNECTIONS, &ap_hard_limit_connections);
  ap_mpm_query(AP_MPMQ_MAX_WORKER_DAEMONS, &ap_max_worker_daemons);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_WORKER_DAEMONS, &ap_max_spare_worker_daemons);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_WORKER_DAEMONS, &ap_min_spare_worker_daemons);
  ap_mpm_query(AP_MPMQ_MAX_DAEMONS_PER_CHILD, &ap_max_daemons_per_child);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_DAEMONS_PER_CHILD, &ap_max_spare_daemons_per_child);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_DAEMONS_PER_CHILD, &ap_min_spare_daemons_per_child);
  ap_mpm_query(AP_MPMQ_MAX_REQUESTS_PER_DAEMON, &ap_max_requests_per_daemon);
  ap_mpm_query(AP_MPMQ_MAX_MEM_PER_DAEMON, &ap_max_mem_per_daemon);
  ap_mpm_query(AP_MPMQ_HARD_LIMIT_MEM_PER_DAEMON, &ap_hard_limit_mem_per_daemon);
  ap_mpm_query(AP_MPMQ_MAX_WORKER_THREADS_PER_DAEMON, &ap_max_worker_threads_per_daemon);
  ap_mpm_query(AP_MPMQ_MAX_SPARE_WORKER_THREADS_PER_DAEMON, &ap_max_spare_worker_threads_per_daemon);
  ap_mpm_query(AP_MPMQ_MIN_SPARE_WORKER_THREADS_PER_DAEMON, &ap_min_spare_worker_threads_per_daemon);
  ap_mpm_query(AP_MPMQ_MAX_THREADS_PER_DAEMON, &ap_max_threads_);