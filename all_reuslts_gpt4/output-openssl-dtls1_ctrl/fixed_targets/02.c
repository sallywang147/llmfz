#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <openssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    // Create a new SSL object
    SSL_CTX* ctx = SSL_CTX_new(DTLS_method());
    if (ctx == nullptr) {
        return 0;
    }

    SSL* ssl = SSL_new(ctx);
    if (ssl == nullptr) {
        SSL_CTX_free(ctx);
        return 0;
    }

    // Get command and larg from the fuzzed data
    int cmd = fuzzed_data.ConsumeIntegral<int>();
    size_t larg = fuzzed_data.ConsumeIntegral<size_t>();

    // Get parg from the fuzzed data
    std::string parg = fuzzed_data.ConsumeRemainingBytesAsString();

    // Call the target function
    dtls1_ctrl(ssl, cmd, larg, const_cast<char*>(parg.c_str()));

    // Clean up
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    ERR_free_strings();

    return 0;
}