#include <stddef.h>
#include <arpa/inet.h>

#include "ares.h"

extern "C" {
#include "ares_nameser.h"
}

int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned