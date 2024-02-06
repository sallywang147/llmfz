#include <fuzzer/FuzzedDataProvider.h>
#include "libssh/libssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize ssh session
    ssh_session my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        return 0;
    }

    // Extract username from the fuzzed data
    std::string username = stream.ConsumeRandomLengthString();
    if (username.empty()) {
        ssh_free(my_ssh_session);
        return 0;
    }

    // Initialize public key
    ssh_key pubkey;
    if (ssh_pki_generate(SSH_KEYTYPE_RSA, 2048, &pubkey) != SSH_OK) {
        ssh_free(my_ssh_session);
        return 0;
    }

    // Call the function to be fuzzed
    ssh_userauth_agent_publickey(my_ssh_session, username.c_str(), pubkey);

    // Clean up
    ssh_key_free(pubkey);
    ssh_free(my_ssh_session);

    return 0;
}