#include <botan/botan.h>
#include <botan/ecdsa.h>

#include <iostream>

extern "C" {
#include <botan/pkcs8.h>
}

int main() {
    Botan::LibraryInitializer init;

    // Generate a new ECDSA key pair
    Botan::AutoSeeded_RNG rng;
    Botan::EC_PrivateKey ec_private_key(rng, Botan::OID("secp256r1"));

    // Export the private key in PKCS#8 format
    std::vector<uint8_t> pkcs8_encoded_key = Botan::PKCS8::PEM_encode(ec_private_key);

    // Import the private key from PKCS#8 format
    Botan::DataSource_Memory pkcs8_source(pkcs8_encoded_key);
    Botan::PKCS8::BER_Decoder pkcs8_decoder(pkcs8_source);
    Botan::Private_Key* imported_private_key = pkcs8_decoder.decode<Botan::Private_Key>();

    // Check if the imported private key is valid
    if (imported_private_key) {
        std::cout << "Successfully imported private key" << std::endl;
    } else {
        std::cout << "Error importing private key" << std::endl;
    }

    return 0;
}