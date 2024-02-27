#include <botan/botan.h>
#include <botan/ecdsa.h>

extern "C" {
#include <botan/internal/pk_ops.h>
}

int main() {
    Botan::EC_PrivateKey key("p256", Botan::OID("1.2.840.10045.3.1.7"), nullptr, 0, true);
    return 0;
}