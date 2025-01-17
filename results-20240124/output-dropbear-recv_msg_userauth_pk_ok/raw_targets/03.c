 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "auth.h"
#include "buffer.h"
#include "common.h"
#include "dbutil.h"
#include "dropbear.h"
#include "dropbear_types.h"
#include "input.h"
#include "key.h"
#include "messages.h"
#include "network.h"
#include "session.h"
#include "ssh.h"
#include "sshbuf.h"
#include "userauth.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t version = stream.ConsumeIntegral<uint8_t>();
  const uint8_t packet_type = stream.ConsumeIntegral<uint8_t>();
  const uint32_t packet_length = stream.ConsumeIntegral<uint32_t>();
  const uint32_t padding_length = stream.ConsumeIntegral<uint32_t>();
  const uint8_t payload[] = {version, packet_type, packet_length, padding_length};
  struct ssh_channel* channel = (struct ssh_channel*)calloc(1, sizeof(struct ssh_channel));
  channel->type = SSH_CHANNEL_USER;
  channel->session = (struct ssh_session*)calloc(1, sizeof(struct ssh_session));
  channel->session->authstate.auth_stage = SSH_AUTH_USER_PASS;
  channel->input_state = INPUT_USERAUTH;
  channel->input_buffer = buf_new(1024);
  channel->input_buffer->len = 0;
  channel->input_buffer->size = 1024;
  buf_putbytes(channel->input_buffer, payload, sizeof(payload));
  recv_msg_userauth_pk_ok(channel);
  buf_free(channel->input_buffer);
  free(channel->session);
  free(channel);
  return 0;
}