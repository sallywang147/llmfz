 #include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    hFILE *memfile;
    uint8_t *copy = malloc(size);
    if (copy == NULL) {
        abort();
    }
    memcpy(copy, data, size);
    // hopen does not take ownership of `copy`, but hts_hopen does.
    memfile = hopen("mem:", "rb:", copy, size);
    if (memfile == NULL) {
        free(copy);
        return 0;
    }

    htsFile *ht_file = hts_hopen(memfile, "data", "rb");
    if (ht_file == NULL) {
        if (hclose(memfile) != 0) {
            abort();
        }
        return 0;
    }
    if (ht_file->format.category != sequence_data) {
        hts_close(ht_file);
        return 0;
    }
    samFile *sam_file = sam_open_format(ht_file, "rb", NULL);
    if (sam_file == NULL) {
        hts_close(ht_file);
        return 0;
    }
    sam_close(sam_file);

    char *fn = strdup("/dev/null");
    if (fn == NULL) {
        abort();
    }
    int min_shift = 0;
    int ret = sam_index_build(fn, min_shift);
    free(fn);
    hts_close(ht_file);
    return ret;
}