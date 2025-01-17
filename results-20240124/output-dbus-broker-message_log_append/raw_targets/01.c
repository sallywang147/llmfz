 #include <stddef.h>
#include <stdint.h>

#include "dbus/message.h"

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        _c_cleanup_(message_unrefp) Message *message = NULL;
        MessageHeader *header = (void *)data;
        int r;

        if (size < sizeof(MessageHeader))
                return;

        r = message_new_incoming(&message, *header);
        if (r != 0)
                return;

        if (message->n_data > size)
                return;

        memcpy(message->data + sizeof(*header), data + sizeof(*header), message->n_data - sizeof(*header));

        r = message_parse_metadata(message);
        if (r)
                return;

        message_stitch_sender(message, 1);

        message_log_append(message, NULL);
}