#include <fuzzer/FuzzedDataProvider.h>
#include "libyang.h"
#include "parser_yang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct lysp_ctx pctx;
    struct lysp_ext_instance ext;

    // Initialize the context and extension instance
    pctx.ctx = ly_ctx_new(NULL, 0);
    ext.name = stream.ConsumeRandomLengthString().c_str();
    ext.argument = stream.ConsumeRandomLengthString().c_str();
    ext.parent = NULL; // No parent for this test
    ext.insubstmt = LYEXT_SUBSTMT_SELF;
    ext.insubstmt_index = 0;
    ext.format = LYS_IN_YANG;
    ext.module = NULL; // No module for this test
    ext.priv = NULL; // No private data for this test

    // Call the function to fuzz
    yangdata_parse(&pctx, &ext);

    // Cleanup
    ly_ctx_destroy(pctx.ctx, NULL);

    return 0;
}