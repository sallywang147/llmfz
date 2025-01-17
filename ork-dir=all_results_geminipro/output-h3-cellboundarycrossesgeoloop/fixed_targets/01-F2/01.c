#include <fuzzer/FuzzedDataProvider.h>
#include <gdal.h>
#include <ogr_api.h>
#include <ogr_geometry.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  GDALDriverH driver = GDALGetDriverByName("GeoJSON");
  if (driver == nullptr) {
    return 0;
  }

  OGRDataSourceH ds = GDALOpenEx("/vsimem/input", GDAL_OF_UPDATE, &driver, nullptr, nullptr);
  if (ds == nullptr) {
    return 0;
  }

  OGRLayerH layer = GDALGetLayerByName(ds, "layer");
  if (layer == nullptr) {
    GDALClose(ds);
    return 0;
  }

  OGRFeatureH feat = OGR_G_CreateFeature(layer, nullptr);
  if (feat == nullptr) {
    GDALClose(ds);
    return 0;
  }

  OGRGeometryH geom = OGR_G_CreateGeometryFromWkt(
      stream.ConsumeRandomLengthString().c_str(), nullptr);
  if (geom == nullptr) {
    OGR_G_DestroyGeometry(geom);
    OGR_F_DestroyFeature(feat);
    GDALClose(ds);
    return 0;
  }

  OGR_G_SetSpatialFilter(layer, geom);
  OGR_F_SetGeometry(feat, geom);
  OGR_G_DestroyGeometry(geom);

  OGRFeatureH next_feat = nullptr;
  while ((next_feat = OGR_L_GetNextFeature(layer)) != nullptr) {
    OGRGeometryH feat_geom = OGR_F_GetGeometryRef(next_feat);
    if (feat_geom == nullptr) {
      OGR_F_DestroyFeature(next_feat);
      continue;
    }

    OGRwkbGeometryType feat_type = OGR_G_GetGeometryType(feat_geom);
    if (feat_type != wkbLineString && feat_type != wkbMultiLineString) {
      OGR_F_DestroyFeature(next_feat);
      continue;
    }

    OGRLinearRingH feat_ring = nullptr;
    if (feat_type == wkbLineString) {
      feat_ring = OGR_G_GetLinearRing(feat_geom, 0);
    } else {
      feat_ring = OGR_G_GetLinearRing(OGR_G_GetGeometryRef(next_feat), 0);
    }

    OGRPointH feat_point = OGR_G_GetPoint(feat_ring, 0);
    OGRPointH feat_point_last = OGR_G_GetPoint(feat_ring, OGR_G_GetPointCount(feat_ring) - 1);

    OGREnvelope feat_env;
    OGR_G_GetEnvelope(feat_geom, &feat_env);

    OGRCellBoundary boundary;
    boundary.nPoints = 2;
    boundary.paPoints = (OGRPointH *)CPLMalloc(sizeof(OGRPointH) * boundary.nPoints);
    boundary.paPoints[0] = *feat_point;
    boundary.paPoints[1] = *feat_point_last;

    OGREnvelope boundary_env;
    OGR_G_GetEnvelope(&boundary, &boundary_env);

    bool result = cellBoundaryCrossesGeoLoop(nullptr, &feat_env, &boundary, &boundary_env);

    CPLFree(boundary.paPoints);
    OGR_F_DestroyFeature(next_feat);
  }

  OGR_F_DestroyFeature(feat);
  GDALClose(ds);

  return 0;
}