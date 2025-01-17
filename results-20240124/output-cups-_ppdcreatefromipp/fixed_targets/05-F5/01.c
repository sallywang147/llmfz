#include <stdio.h>
#include <ppd/ppd.h>

extern "C" {
#include <cups/cups.h>
}

int main() {
    ppd_file_t *ppd = ppdCreateFromIPP(NULL);
    if (!ppd) {
        fprintf(stderr, "Error creating PPD file.\n");
        return 1;
    }

    ppdFree(ppd);
    return 0;
}