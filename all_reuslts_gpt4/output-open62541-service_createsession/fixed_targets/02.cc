#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ua_server.h"
#include "ua_securechannel.h"
#include "ua_types_generated.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize server
  UA_ServerConfig *config = UA_ServerConfig_new_default();
  UA_Server *server = UA_Server_new(config);

  // Initialize channel
  UA_SecureChannel *channel = (UA_SecureChannel*)UA_malloc(sizeof(UA_SecureChannel));
  UA_SecureChannel_init(channel);

  // Initialize request
  UA_CreateSessionRequest *request = UA_CreateSessionRequest_new();
  UA_CreateSessionRequest_init(request);

  // Initialize response
  UA_CreateSessionResponse *response = UA_CreateSessionResponse_new();
  UA_CreateSessionResponse_init(response);

  // Call the function to be fuzzed
  Service_CreateSession(server, channel, request, response);

  // Cleanup
  UA_Server_delete(server);
  UA_ServerConfig_delete(config);
  UA_SecureChannel_deleteMembersCleanup(channel);
  UA_free(channel);
  UA_CreateSessionRequest_delete(request);
  UA_CreateSessionResponse_delete(response);

  return 0;
}