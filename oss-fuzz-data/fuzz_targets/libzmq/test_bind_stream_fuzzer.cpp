/* SPDX-License-Identifier: MPL-2.0 */

#ifdef ZMQ_USE_FUZZING_ENGINE
#include <fuzzer/FuzzedDataProvider.h>
#endif

#include "testutil.hpp"
#include "testutil_unity.hpp"

// Test that the ZMTP engine handles invalid handshake when binding
// https://rfc.zeromq.org/spec/37/
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  setup_test_context();
  char my_endpoint[MAX_SOCKET_STRING];
  void *server = test_context_socket(ZMQ_STREAM);
  //  As per API by default there's no limit to the size of a message,
  //  but the sanitizer allocator will barf over a gig or so
  int64_t max_msg_size = 64 * 1024 * 1024;
  TEST_ASSERT_SUCCESS_ERRNO(zmq_setsockopt(server, ZMQ_MAXMSGSIZE, &max_msg_size, sizeof(int64_t)));
  bind_loopback_ipv4(server, my_endpoint, sizeof(my_endpoint));
  fd_t client = connect_socket(my_endpoint);

  //  If there is not enough data for a full greeting, just send what we can
  //  Otherwise send greeting first, as expected by the protocol
  uint8_t buf[64];
  if (size >= 64) {
    send(client, (void *)data, 64, MSG_NOSIGNAL);
    data += 64;
    size -= 64;
  }
  recv(client, buf, 64, MSG_DONTWAIT);
  msleep(250);
  for (ssize_t sent = 0; size > 0 && (sent != -1 || errno == EINTR); size -= sent > 0 ? sent : 0, data += sent > 0 ? sent : 0)
    sent = send(client, (const char *)data, size, MSG_NOSIGNAL);
  msleep(250);

  zmq_msg_t msg;
  zmq_msg_init(&msg);
  while (-1 != zmq_msg_recv(&msg, server, ZMQ_DONTWAIT)) {
    zmq_msg_close(&msg);
    zmq_msg_init(&msg);
  }

  void *client_good = test_context_socket(ZMQ_DEALER);
  TEST_ASSERT_SUCCESS_ERRNO(zmq_connect(client_good, my_endpoint));

  TEST_ASSERT_EQUAL_INT(6, zmq_send_const(client_good, "HELLO", 6, 0));
  zmq_msg_t routing_id;
  TEST_ASSERT_SUCCESS_ERRNO(zmq_msg_init(&routing_id));
  TEST_ASSERT_SUCCESS_ERRNO(zmq_msg_recv(&routing_id, server, 0));
  TEST_ASSERT_TRUE(zmq_msg_more(&routing_id));
  char const *peer_address = zmq_msg_gets(&routing_id, "Peer-Address");
  zmq_msg_close(&routing_id);
  TEST_ASSERT_NOT_NULL(peer_address);
  TEST_ASSERT_EQUAL_STRING("127.0.0.1", peer_address);
  TEST_ASSERT_EQUAL_INT(0, TEST_ASSERT_SUCCESS_ERRNO(zmq_recv(server, buf, 64, 0)));
  zmq_msg_init(&msg);
  while (-1 != zmq_msg_recv(&msg, server, ZMQ_DONTWAIT)) {
    zmq_msg_close(&msg);
    zmq_msg_init(&msg);
  }

  close(client);
  test_context_socket_close_zero_linger(client_good);
  test_context_socket_close_zero_linger(server);
  teardown_test_context();

  return 0;
}

#ifndef ZMQ_USE_FUZZING_ENGINE
void test_bind_stream_fuzzer() {
  uint8_t **data;
  size_t *len, num_cases = 0;
  if (fuzzer_corpus_encode("tests/libzmq-fuzz-corpora/test_bind_stream_fuzzer_seed_corpus", &data, &len, &num_cases) != 0)
    exit(77);

  while (num_cases-- > 0) {
    TEST_ASSERT_SUCCESS_ERRNO(LLVMFuzzerTestOneInput(data[num_cases], len[num_cases]));
    free(data[num_cases]);
  }

  free(data);
  free(len);
}

int main(int argc, char **argv) {
  setup_test_environment();

  UNITY_BEGIN();
  RUN_TEST(test_bind_stream_fuzzer);

  return UNITY_END();
}
#endif
