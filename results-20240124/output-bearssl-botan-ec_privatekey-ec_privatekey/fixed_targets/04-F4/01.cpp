#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/pkcs8.h>
#include <botan/x509_key.h>

#include <iostream>

int main() {
    Botan::AutoSeededRNG rng;
    Botan::EC_PrivateKey key(rng, Botan::OID("secp256r1"));

    // Generate a PKCS#8 private key
    Botan::PKCS8::PEM_Encoder pem_encoder(rng, "password");
    pem_encoder.start_private_key("EC", key);
    pem_encoder.end_contents();

    // Write the private key to a file
    std::ofstream pem_file("private_key.pem");
    pem_file << pem_encoder.result();
    pem_file.close();

    // Read the private key from the file
    std::ifstream pem_file2("private_key.pem");
    std::string pem_data((std::istreambuf_iterator<char>(pem_file2)), std::istreambuf_iterator<char>());
    pem_file2.close();

    // Parse the private key
    Botan::DataSource_Memory pem_source(pem_data);
    Botan::PKCS8::PEM_Decoder pem_decoder(pem_source, "password");
    Botan::Private_Key* loaded_key = pem_decoder.private_key();

    // Check if the private key is valid
    if (loaded_key == nullptr) {
        std::cout << "Error: Invalid private key" << std::endl;
        return 1;
    }

    // Print the public key
    std::cout << "Public key: " << loaded_key->public_key().public_key_info() << std::endl;

    // Clean up
    delete loaded_key;

    return 0;
}