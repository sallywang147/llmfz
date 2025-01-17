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

    samFile *in = sam_open_format(ht_file, "rb", NULL);
    if (in == NULL) {
        hts_close(ht_file);
        return 0;
    }

    bam_index_build(sam_hdr_name(in->header), -1);
    sam_close(in);
    hts_close(ht_file);
    return 0;
}