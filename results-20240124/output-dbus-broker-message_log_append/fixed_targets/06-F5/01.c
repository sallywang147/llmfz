#include <stddef.h>
#include <stdint.h>
#include "dbus/message.h"

extern "C" {
#include <dbus/dbus.h>
#include <dbus/log.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  _c_cleanup_(message_unrefp) Message *message = NULL;
  MessageHeader *header = (void *)data;
  int r;

  if (size < sizeof(MessageHeader))
    return 0;

  r = message_new_incoming(&message, *header);
  if (r != 0)
    return 0;

  if (message->n_data > size)
    return 0;

  memcpy(message->data + sizeof(*header), data + sizeof(*header), message->n_data - sizeof(*header));

  r = message_parse_metadata(message);
  if (r)
    return 0;

  message_stitch_sender(message, 1);

  _c_cleanup_(log_unrefp) Log *log = NULL;
  log = log_new(LOG_SYSTEM, LOG_INFO, NULL, NULL);
  if (!log)
    return 0;

  message_log_append(message, log);

  return 0;
}