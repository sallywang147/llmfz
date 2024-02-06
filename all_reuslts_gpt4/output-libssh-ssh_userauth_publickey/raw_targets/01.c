#include <libssh/libssh.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize SSH Session
    ssh_session session = ssh_new();
    if(session == NULL) {
        return 0;
    }

    // Extract username
    std::string username = stream.ConsumeRandomLengthString();
    if(username.empty()) {
        ssh_free(session);
        return 0;
    }

    // Initialize SSH Key
    ssh_key privkey;
    int rc = ssh_pki_generate(SSH_KEYTYPE_RSA, 2048, &privkey);
    if(rc != SSH_OK) {
        ssh_free(session);
        return 0;
    }

    // Call the target function
    ssh_userauth_publickey(session, username.c_str(), privkey);

    // Clean up
    ssh_key_free(privkey);
    ssh_free(session);

    return 0;
}