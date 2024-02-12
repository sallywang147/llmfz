 #include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "avahi-common/defs.h"
#include "avahi-common/error.h"
#include "avahi-common/malloc.h"
#include "avahi-common/string.h"
#include "avahi-common/thread-watch.h"
#include "avahi-common/thread-watch-unix.h"
#include "avahi-core/core.h"
#include "avahi-core/log.h"
#include "avahi-core/lookup.h"
#include "avahi-core/protocol.h"
#include "avahi-core/stringlist.h"

void log_function(AvahiLogLevel level, const char *txt) {}

struct AvahiStringList * avahi_string_list_add_printf(struct AvahiStringList * l, char * format) {
  char *tmp;
  struct AvahiStringList *ret;

  if (!l)
    return NULL;

  if (vasprintf(&tmp, format, l->string_list) < 0)
    return NULL;

  ret = avahi_string_list_add(l, tmp);
  free(tmp);

  return ret;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  AvahiClient *client = NULL;
  AvahiServer *server = NULL;
  AvahiLookup *lookup = NULL;
  AvahiStringList *lookup_types = NULL;
  AvahiStringList *lookup_domains = NULL;
  AvahiLookupFlags lookup_flags = 0;
  AvahiProtocol *protocol = NULL;
  AvahiEntryGroup *group = NULL;
  AvahiEntryGroupIter iter;
  AvahiEntry *entry;
  int ret;

  avahi_set_log_function(log_function);

  if (avahi_client_new(&client, AVAHI_CLIENT_NO_FAIL, NULL, NULL) != AVAHI_OK)
    goto finish;

  if (avahi_server_new(&server, AVAHI_SERVER_NO_FAIL, client, NULL, NULL) != AVAHI_OK)
    goto finish;

  if (avahi_protocol_new(&protocol, AVAHI_PROTO_INET, AVAHI_PROTO_UNSPEC, server, NULL) != AVAHI_OK)
    goto finish;

  if (avahi_lookup_new(&lookup, client, protocol, AVAHI_IF_UNSPEC, lookup_types, lookup_domains, lookup_flags, NULL) != AVAHI_OK)
    goto finish;

  ret = avahi_lookup_add(lookup);
  if (ret != AVAHI_OK)
    goto finish;

  if (avahi_entry_group_new(&group, client) != AVAHI_OK)
    goto finish;

  avahi_entry_group_update(group, lookup);

  avahi_entry_group_reset(group);
  avahi_entry_group_next(group, &iter);

  while ((entry = avahi_entry_group_get(&iter))) {
    avahi_string_list_add_printf(lookup_types, "%s", entry->type);
    avahi_string_list_add_printf(lookup_domains, "%s", entry->domain);
    avahi_entry_group_next(group, &iter);
  }

finish:
  if (group)
    avahi_entry_group_free(group);
  if (lookup)
    avahi_lookup_free(lookup);
  if (protocol)
    avahi_protocol_free(protocol);
  if (server)
    avahi_server_free(server);
  if (client)
    avahi_client_free(client);

  return 0;
}