#include <botan/botan.h>
#include <botan/pkcs8.h>

#include <iostream>

int main() {
    Botan::DataSource_Memory data("-----BEGIN EC PRIVATE KEY-----"
                                 "MHcCAQEEIE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCCqGSM49"
                                 "AwEHoUQDQgAE081/0v6878X83/267pZ464843290876543210860qAoGCC