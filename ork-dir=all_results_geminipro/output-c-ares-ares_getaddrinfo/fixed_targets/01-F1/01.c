#include <stddef.h>

#include <ares.h>

extern "C" {
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
}

int LLVMFuzzerTestOneInput