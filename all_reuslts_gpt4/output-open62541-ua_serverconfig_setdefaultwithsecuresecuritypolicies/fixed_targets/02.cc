#include <fuzzer/FuzzedDataProvider.h>
#include <open62541/server_config_default.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UA_ServerConfig *conf = UA_ServerConfig_new_minimal(4840, nullptr);
  short portNumber = stream.ConsumeIntegral<short>();

  UA_String certificate;
  UA_String privateKey;
  UA_String trustList;
  UA_String issuerList;
  UA_String revocationList;

  std::string certificateStr = stream.ConsumeRandomLengthString();
  certificate.length = certificateStr.size();
  certificate.data = (UA_Byte*)certificateStr.c_str();

  std::string privateKeyStr = stream.ConsumeRandomLengthString();
  privateKey.length = privateKeyStr.size();
  privateKey.data = (UA_Byte*)privateKeyStr.c_str();

  size_t trustListSize = stream.ConsumeIntegral<size_t>();
  std::string trustListStr = stream.ConsumeBytesAsString(trustListSize);
  trustList.length = trustListStr.size();
  trustList.data = (UA_Byte*)trustListStr.c_str();

  size_t issuerListSize = stream.ConsumeIntegral<size_t>();
  std::string issuerListStr = stream.ConsumeBytesAsString(issuerListSize);
  issuerList.length = issuerListStr.size();
  issuerList.data = (UA_Byte*)issuerListStr.c_str();

  size_t revocationListSize = stream.ConsumeIntegral<size_t>();
  std::string revocationListStr = stream.ConsumeBytesAsString(revocationListSize);
  revocationList.length = revocationListStr.size();
  revocationList.data = (UA_Byte*)revocationListStr.c_str();

  UA_ServerConfig_setDefaultWithSecureSecurityPolicies(conf, portNumber, &certificate, &privateKey, &trustList, trustListSize, &issuerList, issuerListSize, &revocationList, revocationListSize);

  UA_ServerConfig_delete(conf);

  return 0;
}