 #include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../htslib/hfile.h"
#include "../../htslib/hts.h"
#include "../../htslib/sam.h"
#include "../../htslib/vcf.h"

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
    if (ht_file->format.category != variant_data) {
        hts_close(ht_file);
        return 0;
    }
    bcf_hdr_t *hdr = bcf_hdr_read(ht_file);
    if (hdr == NULL) {
        hts_close(ht_file);
        return 0;
    }

    char *fn = (char *)malloc(100);
    if (fn == NULL) {
        bcf_hdr_destroy(hdr);
        hts_close(ht_file);
        return 0;
    }
    strcpy(fn, "out.csi");
    bcf_index_build(fn, 0);
    free(fn);

    bcf_hdr_destroy(hdr);
    hts_close(ht_file);
    return 0;
}