#include "aflHarness.h"
#include "geo.h"
#include "geo_loop.h"
#include "geo_types.h"

typedef struct {
    GeoLoop *geoloop;
    BBox loopBBox;
    CellBoundary boundary;
    BBox boundaryBBox;
} inputArgs;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < sizeof(inputArgs)) {
        return 0;
    }
    const inputArgs *args = (const inputArgs *)data;

    bool result = cellBoundaryCrossesGeoLoop(args->geoloop, &args->loopBBox,
                                           &args->boundary, &args->boundaryBBox);

    return 0;
}

AFL_HARNESS_MAIN(sizeof(inputArgs));