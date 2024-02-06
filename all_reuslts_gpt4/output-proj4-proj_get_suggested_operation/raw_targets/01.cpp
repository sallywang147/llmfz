#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <proj.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a pj_ctx object
    struct pj_ctx *ctx = proj_context_create();

    // Create a PJ_OBJ_LIST object
    struct PJ_OBJ_LIST *obj_list = (struct PJ_OBJ_LIST *)malloc(sizeof(struct PJ_OBJ_LIST));

    // Extract an integer
    int int_arg = stream.ConsumeIntegral<int>();

    // Create a PJ_COORD object
    union PJ_COORD *coord = (union PJ_COORD *)malloc(sizeof(union PJ_COORD));

    // Call the target function
    proj_get_suggested_operation(ctx, obj_list, int_arg, coord);

    // Cleanup
    proj_context_destroy(ctx);
    free(obj_list);
    free(coord);

    return 0;
}