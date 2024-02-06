#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "open62541/server_config_default.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UA_ServerConfig *conf = UA_ServerConfig_new_minimal(4840, NULL);
  if(!conf) {
    return 0;
  }

  short portNumber = stream.ConsumeIntegral<short>();

  UA_String certificate;
  size_t certificateSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/5);
  std::string certificateStr = stream.ConsumeBytesAsString(certificateSize);
  certificate.length = certificateSize;
  certificate.data = (UA_Byte*)certificateStr.c_str();

  UA_String privateKey;
  size_t privateKeySize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/4);
  std::string privateKeyStr = stream.ConsumeBytesAsString(privateKeySize);
  privateKey.length = privateKeySize;
  privateKey.data = (UA_Byte*)privateKeyStr.c_str();

  size_t trustListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/3);
  UA_String *trustList = (UA_String*)malloc(sizeof(UA_String) * trustListSize);
  for(size_t i = 0; i < trustListSize; i++) {
    size_t strSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/(2*trustListSize));
    std::string str = stream.ConsumeBytesAsString(strSize);
    trustList[i].length = strSize;
    trustList[i].data = (UA_Byte*)str.c_str();
  }

  size_t issuerListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/2);
  UA_String *issuerList = (UA_String*)malloc(sizeof(UA_String) * issuerListSize);
  for(size_t i = 0; i < issuerListSize; i++) {
    size_t strSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/(issuerListSize));
    std::string str = stream.ConsumeBytesAsString(strSize);
    issuerList[i].length = strSize;
    issuerList[i].data = (UA_Byte*)str.c_str();
  }

  size_t revocationListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  UA_String *revocationList = (UA_String*)malloc(sizeof(UA_String) * revocationListSize);
  for(size_t i = 0; i < revocationListSize; i++) {
    size_t strSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes()/(revocationListSize));
    std::string str = stream.ConsumeBytesAsString(strSize);
    revocationList[i].length = strSize;
    revocationList[i].data = (UA_Byte*)str.c_str();
  }

  UA_ServerConfig_setDefaultWithSecureSecurityPolicies(conf, portNumber, &certificate, &privateKey, trustList, trustListSize, issuerList, issuerListSize, revocationList, revocationListSize);

  UA_ServerConfig_delete(conf);
  free(trustList);
  free(issuerList);
  free(revocationList);

  return 0;
}