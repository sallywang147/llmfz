#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "open62541.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    UA_ServerConfig *conf = UA_ServerConfig_new_minimal(4840, NULL);
    if (conf == NULL) {
        return 0;
    }

    short portNumber = stream.ConsumeIntegral<short>();

    UA_String certificate;
    certificate.length = stream.ConsumeIntegralInRange<size_t>(0, size);
    certificate.data = (UA_Byte*) stream.ConsumeBytes<uint8_t>(certificate.length).data();

    UA_String privateKey;
    privateKey.length = stream.ConsumeIntegralInRange<size_t>(0, size);
    privateKey.data = (UA_Byte*) stream.ConsumeBytes<uint8_t>(privateKey.length).data();

    size_t trustListSize = stream.ConsumeIntegralInRange<size_t>(0, 10);
    UA_String *trustList = (UA_String*) malloc(trustListSize * sizeof(UA_String));
    for (size_t i = 0; i < trustListSize; i++) {
        trustList[i].length = stream.ConsumeIntegralInRange<size_t>(0, size);
        trustList[i].data = (UA_Byte*) stream.ConsumeBytes<uint8_t>(trustList[i].length).data();
    }

    size_t issuerListSize = stream.ConsumeIntegralInRange<size_t>(0, 10);
    UA_String *issuerList = (UA_String*) malloc(issuerListSize * sizeof(UA_String));
    for (size_t i = 0; i < issuerListSize; i++) {
        issuerList[i].length = stream.ConsumeIntegralInRange<size_t>(0, size);
        issuerList[i].data = (UA_Byte*) stream.ConsumeBytes<uint8_t>(issuerList[i].length).data();
    }

    size_t revocationListSize = stream.ConsumeIntegralInRange<size_t>(0, 10);
    UA_String *revocationList = (UA_String*) malloc(revocationListSize * sizeof(UA_String));
    for (size_t i = 0; i < revocationListSize; i++) {
        revocationList[i].length = stream.ConsumeIntegralInRange<size_t>(0, size);
        revocationList[i].data = (UA_Byte*) stream.ConsumeBytes<uint8_t>(revocationList[i].length).data();
    }

    UA_ServerConfig_setDefaultWithSecurityPolicies(conf, portNumber, &certificate, &privateKey, trustList, trustListSize, issuerList, issuerListSize, revocationList, revocationListSize);

    free(trustList);
    free(issuerList);
    free(revocationList);
    UA_ServerConfig_delete(conf);

    return 0;
}