#include <fuzzer/FuzzedDataProvider.h>
#include "aflHarness.h"
#include "h3api.h"
#include "utility.h"

typedef struct {
    GeoPolygon geoPolygon;
    BBox bboxes;
    CellBoundary boundary;
    BBox boundaryBBox;
} inputArgs;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    if (size < sizeof(inputArgs)) {
        return 0;
    }

    inputArgs args;
    size_t consumed = stream.ConsumeData(&args, sizeof(args));

    if (consumed != sizeof(args)) {
        return 0;
    }

    cellBoundaryInsidePolygon(&args.geoPolygon, &args.bboxes, &args.boundary, &args.boundaryBBox);

    return 0;
}

AFL_HARNESS_MAIN(sizeof(inputArgs));