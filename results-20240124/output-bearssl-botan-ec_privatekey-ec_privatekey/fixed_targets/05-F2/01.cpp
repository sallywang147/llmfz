#include <botan/botan.h>
#include <botan/ec.h>
#include <botan/pkcs8.h>

using namespace Botan;

int main() {
    // Read a private key from a file
    DataSource_Stream input("private_key.pem");
    PKCS8::BER_Decoder decoder(input);
    auto key = decoder.decode<EC_PrivateKey>();

    // Use the private key to decrypt a message
    SecureVector<byte> ciphertext = { /* ... */ };
    SecureVector<byte> plaintext = key->decrypt(ciphertext);

    // ...
}