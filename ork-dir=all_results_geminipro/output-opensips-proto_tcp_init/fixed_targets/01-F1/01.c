#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "proto_tcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string proto_name = stream.ConsumeRemainingBytesAsString();
  proto_info pi = {
      .name = proto_name.c_str(),
      .proto_init = proto_tcp_init,
      .proto_destroy = proto_tcp_destroy,
      .proto_dump = proto_tcp_dump,
      .proto_get_sock_info = proto_tcp_get_sock_info,
      .proto_set_sock_info = proto_tcp_set_sock_info,
      .proto_send = proto_tcp_send,
      .proto_recv = proto_tcp_recv,
      .proto_accept = proto_tcp_accept,
      .proto_connect = proto_tcp_connect,
      .proto_close = proto_tcp_close,
      .proto_getnameinfo = proto_tcp_getnameinfo,
      .proto_getsockname = proto_tcp_getsockname,
      .proto_getpeername = proto_tcp_getpeername,
      .proto_setsockopt = proto_tcp_setsockopt,
      .proto_getsockopt = proto_tcp_getsockopt,
      .proto_listen = proto_tcp_listen,
      .proto_bind = proto_tcp_bind,
      .proto_shutdown = proto_tcp_shutdown,
      .proto_get_fd = proto_tcp_get_fd,
      .proto_select = proto_tcp_select,
      .proto_poll = proto_tcp_poll,
      .proto_epoll_create = proto_tcp_epoll_create,
      .proto_epoll_ctl = proto_tcp_epoll_ctl,
      .proto_epoll_wait = proto_tcp_epoll_wait,
      .proto_epoll_destroy = proto_tcp_epoll_destroy,
      .proto_get_transport = proto_tcp_get_transport,
      .proto_get_proto_stats = proto_tcp_get_proto_stats,
      .proto_stats = proto_tcp_stats,
      .proto_stats_reset = proto_tcp_stats_reset,
      .proto_get_local_ip = proto_tcp_get_local_ip,
      .proto_get_local_port = proto_tcp_get_local_port,
      .proto_get_remote_ip = proto_tcp_get_remote_ip,
      .proto_get_remote_port = proto_tcp_get_remote_port,
      .proto_tcp_get_accept_queue = proto_tcp_get_accept_queue,
      .proto_tcp_get_accept_queue_len = proto_tcp_get_accept_queue_len,
      .proto_tcp_set_accept_queue_len = proto_tcp_set_accept_queue_len,
      .proto_tcp_get_tcpinfo = proto_tcp_get_tcpinfo,
      .proto_tcp_set_tcpinfo = proto_tcp_set_tcpinfo,
      .proto_tcp_get_tx_queue_len = proto_tcp_get_tx_queue_len,
      .proto_tcp_get_rx_queue_len = proto_tcp_get_rx_queue_len,
      .proto_tcp_get_tx_queue_size = proto_tcp_get_tx_queue_size,
      .proto_tcp_get_rx_queue_size = proto_tcp_get_rx_queue_size,
      .proto_tcp_get_tx_queue_limit = proto_tcp_get_tx_queue_limit,
      .proto_tcp_get_rx_queue_limit = proto_tcp_get_rx_queue_limit,
      .proto_tcp_set_tx_queue_limit = proto_tcp_set_tx_queue_limit,
      .proto_tcp_set_rx_queue_limit = proto_tcp_set_rx_queue_limit,
      .proto_tcp_get_tx_queue_drops = proto_tcp_get_tx_queue_drops,
      .proto_tcp_get_rx_queue_drops = proto_tcp_get_rx_queue_drops,
      .proto_tcp_get_tx_queue_flushes = proto_tcp_get_tx_queue_flushes,
      .proto_tcp_get_rx_queue_flushes = proto_tcp_get_rx_queue_flushes,
      .proto_tcp_get_tx_queue_avg = proto_tcp_get_tx_queue_avg,
      .proto_tcp_get_rx_queue_avg = proto_tcp_get_rx_queue_avg,
      .proto_tcp_get_tx_queue_max = proto_tcp_get_tx_queue_max,
      .proto_tcp_get_rx_queue_max = proto_tcp_get_rx_queue_max,
      .proto_tcp_get_tx_queue_stddev = proto_tcp_get_tx_queue_stddev,
      .proto_tcp_get_rx_queue_stddev = proto_tcp_get_rx_queue_stddev,
      .proto_tcp_get_tx_queue_histogram = proto_tcp_get_tx_queue_histogram,
      .proto_tcp_get_rx_queue_histogram = proto_tcp_get_rx_queue_histogram,
      .proto_tcp_get_tx_queue_histogram_len = proto_tcp_get_tx_queue_histogram_len,
      .proto_tcp_get_rx_queue_histogram_len = proto_tcp_get_rx_queue_histogram_len,
      .proto_tcp_reset_tx_queue_stats = proto_tcp_reset_tx_queue_stats,
      .proto_tcp_reset_rx_queue_stats = proto_tcp_reset_rx_queue_stats,
      .proto_tcp_get_tx_queue_stats = proto_tcp_get_tx_queue_stats,
      .proto_tcp_get_rx_queue_stats = proto_tcp_get_rx_queue_stats,
      .proto_tcp_get_tx_queue_stats_len = proto_tcp_get_tx_queue_stats_len,
      .proto_tcp_get_rx_queue_stats_len = proto_tcp_get_rx_queue_stats_len,
      .proto_tcp_get_tx_queue_stats_histogram =
          proto_tcp_get_tx_queue_stats_histogram,
      .proto_tcp_get_rx_queue_stats_histogram =
          proto_tcp_get_rx_queue_stats_histogram,
      .proto_tcp_get_tx_queue_stats_histogram_len =
          proto_tcp_get_tx_queue_stats_histogram_len,
      .proto_tcp_get_rx_queue_stats_histogram_len =
          proto_tcp_get_rx_queue_stats_histogram_len,
      .proto_tcp_reset_tx_queue_stats_histogram =
          proto_tcp_reset_tx_queue_stats_histogram,
      .proto_tcp_reset_rx_queue_stats_histogram =
          proto_tcp_reset_rx_queue_stats_histogram,
      .proto_tcp_get_tx_queue_stats_histogram_stats =
          proto_tcp_get_tx_queue_stats_histogram_stats,
      .proto_tcp_get_rx_queue_stats_histogram_stats =
          proto_tcp_get_rx_queue_stats_histogram_stats,
      .proto_tcp_get_tx_queue_stats_histogram_stats_len =
          proto_tcp_get_tx_queue_stats_histogram_stats_len,
      .proto_tcp_get_rx_queue_stats_histogram_stats_len =
          proto_tcp_get_rx_queue_stats_histogram_stats_len,
      .proto_tcp_reset_tx_queue_stats_histogram_stats =
          proto_tcp_reset_tx_queue_stats_histogram_stats,
      .proto_tcp_reset_rx_queue_stats_histogram_stats =
          proto_tcp_reset_rx_queue_stats_histogram_stats,
      .proto_tcp_get_tx_queue_stats_histogram_stats_histogram =
          proto_tcp_get_tx_queue_stats_histogram_stats_histogram,
      .