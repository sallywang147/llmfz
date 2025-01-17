#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "apr.h"
#include "apr_strings.h"
#include "apr_tables.h"
#include "ap_config.h"
#include "ap_mmn.h"
#include "ap_mpm.h"
#include "http_config.h"
#include "http_connection.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_vhost.h"
#include "mod_core.h"
#include "scoreboard.h"
#include "util_filter.h"
#include "util_script.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  apr_pool_t* pool = apr_pool_create(nullptr, nullptr);
  apr_pool_t* psubpool = apr_pool_create(nullptr, pool);
  apr_pool_t* ptemp = apr_pool_create(nullptr, pool);
  apr_pool_t* pconnection = apr_pool_create(nullptr, pool);
  apr_pool_t* pperdir = apr_pool_create(nullptr, pool);
  apr_pool_t* pperrequest = apr_pool_create(nullptr, pool);
  apr_pool_t* ptransient = apr_pool_create(nullptr, pool);

  apr_status_t rv;
  ap_configfile_t* fconf = ap_pcfg_open_ex(pool, nullptr, nullptr, nullptr);
  ap_directive_t* conf = ap_set_config_vectors(pool, nullptr, nullptr, nullptr);
  ap_directive_t* dirconf = ap_set_config_vectors(pool, nullptr, nullptr, nullptr);

  request_rec* r = (request_rec*)apr_palloc(pool, sizeof(request_rec));
  r->pool = prequest;
  r->connection = (conn_rec*)apr_palloc(pconnection, sizeof(conn_rec));
  r->connection->pool = pconnection;
  r->per_dir_config = dirconf;
  r->server = (server_rec*)apr_palloc(pool, sizeof(server_rec));
  r->server->process->pool = pool;
  r->server->process->ptrans = ptransient;
  r->server->process->pconfig = pconfig;
  r->server->process->ptemp = ptemp;
  r->server->process->pconnection = pconnection;
  r->server->process->pperdir = pperdir;
  r->server->process->pperrequest = pperrequest;
  r->server->process->plisten = pconnection;
  r->server->process->config_vector = conf;
  r->server->process->config_file = fconf;
  r->server->process->pool = pool;
  r->server->process->is_child = 0;
  r->server->process->generation = 0;
  r->server->process->me = (process_rec*)apr_palloc(pool, sizeof(process_rec));
  r->server->process->me->pool = pool;
  r->server->process->me->pconfig = pconfig;
  r->server->process->me->ptemp = ptemp;
  r->server->process->me->pconnection = pconnection;
  r->server->process->me->pperdir = pperdir;
  r->server->process->me->pperrequest = pperrequest;
  r->server->process->me->plisten = pconnection;
  r->server->process->me->config_vector = conf;
  r->server->process->me->config_file = fconf;
  r->server->process->me->pool = pool;
  r->server->process->me->is_child = 0;
  r->server->process->me->generation = 0;
  r->server->process->me->pid = 0;
  r->server->process->me->uniq_id = 0;
  r->server->process->me->start_time = 0;
  r->server->process->me->restart_time = 0;
  r->server->process->me->timeout_conn = 0;
  r->server->process->me->timeout_keepalive = 0;
  r->server->process->me->timeout_idle = 0;
  r->server->process->me->timeout_request = 0;
  r->server->process->me->timeout_shutdown = 0;
  r->server->process->me->timeout_linger = 0;
  r->server->process->me->max_requests_per_child = 0;
  r->server->process->me->max_memory_per_child = 0;
  r->server->process->me->num_children = 0;
  r->server->process->me->num_servers = 0;
  r->server->process->me->num_busy_children = 0;
  r->server->process->me->num_idle_children = 0;
  r->server->process->me->num_requests = 0;
  r->server->process->me->num_connections = 0;
  r->server->process->me->num_bytes_sent = 0;
  r->server->process->me->num_bytes_recvd = 0;
  r->server->process->me->num_accesses = 0;
  r->server->process->me->num_denials = 0;
  r->server->process->me->num_timeouts = 0;
  r->server->process->me->num_busy_slots = 0;
  r->server->process->me->num_idle_slots = 0;
  r->server->process->me->num_slots = 0;
  r->server->process->me->num_reqs_per_child = 0;
  r->server->process->me->num_mems_per_child = 0;
  r->server->process->me->num_children_exited = 0;
  r->server->process->me->num_children_killed = 0;
  r->server->process->me->num_restarts = 0;
  r->server->process->me->num_crashes = 0;
  r->server->process->me->num_retries = 0;
  r->server->process->me->num_config_updates = 0;
  r->server->process->me->num_scoreboard_updates = 0;
  r->server->process->me->num_access_checks = 0;
  r->server->process->me->num_auth_checks = 0;
  r->server->process->me->num_child_exit_status = 0;
  r->server->process->me->num_child_exit_signals = 0;
  r->server->process->me->num_accept_with_lock_failures = 0;
  r->server->process->me->num_accept_serial_failures = 0;
  r->server->process->me->num_accept_filter_failures = 0;
  r->server->process->me->num_accept_invalid_connections = 0;
  r->server->process->me->num_connection_drops = 0;
  r->server->process->me->num_connection_timeouts = 0;
  r->server->process->me->num_connection_write_timeouts = 0;
  r->server->process->me->num_connection_read_timeouts = 0;
  r->server->process->me->num_connection_lingers = 0;
  r->server->process->me->num_connection_aborts = 0;
  r->server->process->me->num_connection_resets = 0;
  r->server->process->me->num_connection_invalid_requests = 0;
  r->server->process->me->num_connection_parse_errors = 0;
  r->server->process->me->num_connection_header_errors = 0;
  r->server->process->me->num_connection_request_errors = 0;
  r->server->process->me->num_connection_internal_errors = 0;
  r->server->process->me->num_connection_bad_headers = 0;
  r->