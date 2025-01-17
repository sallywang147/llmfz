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

  // Initialize server and secure channel
  UA_ServerConfig *config = UA_ServerConfig_new_default();
  UA_Server *server = UA_Server_new(config);
  UA_SecureChannel *channel = (UA_SecureChannel*)UA_malloc(sizeof(UA_SecureChannel));
  UA_SecureChannel_init(channel);

  // Consume data for CreateSessionRequest
  UA_CreateSessionRequest request;
  UA_CreateSessionRequest_init(&request);
  request.requestHeader.timestamp = stream.ConsumeIntegral<UA_DateTime>();
  request.requestHeader.timeoutHint = stream.ConsumeIntegral<UA_UInt32>();
  request.maxResponseMessageSize = stream.ConsumeIntegral<UA_UInt32>();
  request.requestedSessionTimeout = stream.ConsumeFloatingPoint<UA_Double>();

  // Initialize CreateSessionResponse
  UA_CreateSessionResponse response;
  UA_CreateSessionResponse_init(&response);

  // Call the function to fuzz
  Service_CreateSession(server, channel, &request, &response);

  // Cleanup
  UA_CreateSessionResponse_clear(&response);
  UA_CreateSessionRequest_clear(&request);
  UA_SecureChannel_deleteMembers(channel);
  UA_free(channel);
  UA_Server_delete(server);
  UA_ServerConfig_delete(config);

  return 0;
}