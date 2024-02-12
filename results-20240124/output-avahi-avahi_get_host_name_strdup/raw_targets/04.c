 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avahi-common/defs.h"
#include "avahi-common/malloc.h"
#include "avahi-common/simple-watch.h"
#include "avahi-common/thread-watch.h"
#include "avahi-common/timeval.h"
#include "avahi-core/error.h"
#include "avahi-core/server.h"
#include "avahi-core/util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  AvahiServer *server = nullptr;
  AvahiSimplePoll *simple_poll = nullptr;
  AvahiWatch *watch = nullptr;
  AvahiError error;
  AvahiSimplePoll *poll = nullptr;
  char *host_name = nullptr;

  avahi_set_malloc_failure_handler(avahi_malloc_failure_handler);

  avahi_simple_poll_new(&simple_poll);
  avahi_server_new(AVAHI_SERVER_USE_DNS, &server, &error);
  if (server) {
    avahi_server_add_poll(server, simple_poll);
    avahi_server_watch(server, &watch);
    avahi_simple_poll_get(simple_poll, &poll);
  }

  host_name = avahi_get_host_name_strdup();
  free(host_name);

  if (watch)
    avahi_watch_free(watch);
  if (server)
    avahi_server_free(server);
  if (poll)
    avahi_simple_poll_free(poll);
  if (simple_poll)
    avahi_simple_poll_free(simple_poll);

  return 0;
}