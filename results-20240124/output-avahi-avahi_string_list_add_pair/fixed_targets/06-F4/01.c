#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-common/simple-watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/error.h>
#include <avahi-common/timeval.h>
#include <avahi-common/thread-watch.h>
#include <avahi-common/watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/timeval.h>
#include <avahi-common/thread-watch.h>
#include <avahi-common/watch.h>

extern "C" {
#include <avahi-common/simple-watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/error.h>
#include <avahi-common/timeval.h>
#include <avahi-common/thread-watch.h>
#include <avahi-common/watch.h>
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // Create an instance of the Avahi client.
  AvahiClient *client = avahi_client_new(nullptr, 0, nullptr, nullptr);
  if (!client) {
    cerr << "Failed to create Avahi client." << endl;
    return 1;
  }

  // Create a lookup object to find services.
  AvahiLookup *lookup = avahi_simple_poll_new(client, AVAHI_IF_UNSPEC);
  if (!lookup) {
    cerr << "Failed to create Avahi lookup object." << endl;
    avahi_client_free(client);
    return 1;
  }

  // Set the service type and domain to search for.
  const char *serviceType = "_http._tcp";
  const char *domain = "local";
  int result = avahi_simple_poll_add_service(lookup, serviceType, domain);
  if (result < 0) {
    cerr << "Failed to add service to lookup object." << endl;
    avahi_simple_poll_free(lookup);
    avahi_client_free(client);
    return 1;
  }

  // Create a list of found services.
  vector<string> services;

  // Define a callback function to handle service resolution results.
  AvahiLookupCB callback = [](AvahiLookup *l, AvahiLookupResultFlags flags,
                              AvahiServiceResolver *resolver, void *userdata) {
    if (flags & AVAHI_LOOKUP_RESULT_FOUND) {
      // Get the service name and add it to the list.
      const char *name = avahi_service_resolver_get_name(resolver);
      services.push_back(name);
    }
  };

  // Start the lookup operation.
  result = avahi_simple_poll_start(lookup, callback, nullptr);
  if (result < 0) {
    cerr << "Failed to start lookup operation." << endl;
    avahi_simple_poll_free(lookup);
    avahi_client_free(client);
    return 1;
  }

  // Wait for the lookup operation to complete.
  avahi_simple_poll_loop(lookup);

  // Print the list of found services.
  cout << "Found the following services:" << endl;
  for (const string &service : services) {
    cout << service << endl;
  }

  // Clean up the Avahi client and lookup object.
  avahi_simple_poll_free(lookup);
  avahi_client_free(client);

  return 0;
}