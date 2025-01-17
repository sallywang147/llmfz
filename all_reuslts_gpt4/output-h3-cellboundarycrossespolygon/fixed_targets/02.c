#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    GeoPolygon geoPolygon;
    BBox bboxes;
    CellBoundary boundary;
    BBox boundaryBBox;

    // Initialize GeoPolygon
    geoPolygon.geofence.numVerts = stream.ConsumeIntegralInRange<uint32_t>(0, 100);
    geoPolygon.geofence.verts = new GeoCoord[geoPolygon.geofence.numVerts];
    for (uint32_t i = 0; i < geoPolygon.geofence.numVerts; ++i) {
        geoPolygon.geofence.verts[i].lat = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
        geoPolygon.geofence.verts[i].lon = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
    }
    geoPolygon.numHoles = stream.ConsumeIntegralInRange<uint32_t>(0, 10);
    geoPolygon.holes = new Geofence[geoPolygon.numHoles];
    for (uint32_t i = 0; i < geoPolygon.numHoles; ++i) {
        geoPolygon.holes[i].numVerts = stream.ConsumeIntegralInRange<uint32_t>(0, 100);
        geoPolygon.holes[i].verts = new GeoCoord[geoPolygon.holes[i].numVerts];
        for (uint32_t j = 0; j < geoPolygon.holes[i].numVerts; ++j) {
            geoPolygon.holes[i].verts[j].lat = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
            geoPolygon.holes[i].verts[j].lon = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
        }
    }

    // Initialize BBox
    bboxes.north = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    bboxes.south = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    bboxes.east = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
    bboxes.west = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);

    // Initialize CellBoundary
    boundary.numVerts = stream.ConsumeIntegralInRange<uint32_t>(0, 100);
    boundary.verts = new GeoCoord[boundary.numVerts];
    for (uint32_t i = 0; i < boundary.numVerts; ++i) {
        boundary.verts[i].lat = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
        boundary.verts[i].lon = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
    }

    // Initialize boundaryBBox
    boundaryBBox.north = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    boundaryBBox.south = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    boundaryBBox.east = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
    boundaryBBox.west = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);

    // Call the target function
    cellBoundaryCrossesPolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

    // Cleanup
    delete[] geoPolygon.geofence.verts;
    for (uint32_t i = 0; i < geoPolygon.numHoles; ++i) {
        delete[] geoPolygon.holes[i].verts;
    }
    delete[] geoPolygon.holes;
    delete[] boundary.verts;

    return 0;
}