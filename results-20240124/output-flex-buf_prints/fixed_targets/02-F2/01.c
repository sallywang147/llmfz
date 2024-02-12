#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "buf.h"
}

int main() {
    buf_t* buf = buf_new(1024);
    buf_prints(buf, "Hello, world!\n");
    buf_free(buf);
    return 0;
}