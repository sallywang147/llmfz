#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Define and initialize the parameters for cellBoundaryCrossesPolygon function.
    GeoPolygon geoPolygon;
    BBox bboxes;
    CellBoundary boundary;
    BBox boundaryBBox;

    // We need to make sure that the GeoPolygon, BBox and CellBoundary structures are properly initialized.
    // As these are complex structures, we will just zero initialize them for simplicity.
    memset(&geoPolygon, 0, sizeof(geoPolygon));
    memset(&bboxes, 0, sizeof(bboxes));
    memset(&boundary, 0, sizeof(boundary));
    memset(&boundaryBBox, 0, sizeof(boundaryBBox));

    // Now we can call the target function.
    cellBoundaryCrossesPolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

    return 0;
}