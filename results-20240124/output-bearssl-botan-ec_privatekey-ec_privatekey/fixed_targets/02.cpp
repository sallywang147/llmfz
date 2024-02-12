#include <botan/botan.h>
#include <botan/pkcs8.h>

#include <iostream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    Botan::DataSource_Memory mem(data, size);
    Botan::PKCS8::BER_Decoder dec(mem);
    Botan::Private_Key* key = dec.decode<Botan::Private_Key>();
    if(key) {
        delete key;
    }

    // Call the target function
    Botan::EC_PrivateKey ec_key;
    return 0;
}

int main() {
    return 0;
}