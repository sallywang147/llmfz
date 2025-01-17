#include <fuzzer/FuzzedDataProvider.h>
#include <open62541/server_config_default.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    UA_ServerConfig *conf = UA_ServerConfig_new_minimal(4840, NULL);
    if (!conf) {
        return 0;
    }

    short portNumber = stream.ConsumeIntegral<short>();

    UA_String certificate = UA_STRING_NULL;
    UA_String privateKey = UA_STRING_NULL;
    UA_String trustList = UA_STRING_NULL;
    UA_String issuerList = UA_STRING_NULL;
    UA_String revocationList = UA_STRING_NULL;

    if (stream.remaining_bytes() > 0) {
        size_t certificateSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
        certificate = UA_STRING_ALLOC((char*)stream.ConsumeBytes(certificateSize).data());
    }

    if (stream.remaining_bytes() > 0) {
        size_t privateKeySize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
        privateKey = UA_STRING_ALLOC((char*)stream.ConsumeBytes(privateKeySize).data());
    }

    size_t trustListSize = 0;
    if (stream.remaining_bytes() > 0) {
        trustListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
        trustList = UA_STRING_ALLOC((char*)stream.ConsumeBytes(trustListSize).data());
    }

    size_t issuerListSize = 0;
    if (stream.remaining_bytes() > 0) {
        issuerListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
        issuerList = UA_STRING_ALLOC((char*)stream.ConsumeBytes(issuerListSize).data());
    }

    size_t revocationListSize = 0;
    if (stream.remaining_bytes() > 0) {
        revocationListSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
        revocationList = UA_STRING_ALLOC((char*)stream.ConsumeBytes(revocationListSize).data());
    }

    int result = UA_ServerConfig_setDefaultWithSecurityPolicies(conf, portNumber, &certificate, &privateKey, &trustList, trustListSize, &issuerList, issuerListSize, &revocationList, revocationListSize);

    UA_String_deleteMembers(&certificate);
    UA_String_deleteMembers(&privateKey);
    UA_String_deleteMembers(&trustList);
    UA_String_deleteMembers(&issuerList);
    UA_String_deleteMembers(&revocationList);
    UA_ServerConfig_delete(conf);

    return 0;
}