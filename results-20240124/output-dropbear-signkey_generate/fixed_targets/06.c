#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "signkey.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <keyfile>\n", argv[0]);
        return 1;
    }

    signkey_generate(argv[1]);

    return 0;
}