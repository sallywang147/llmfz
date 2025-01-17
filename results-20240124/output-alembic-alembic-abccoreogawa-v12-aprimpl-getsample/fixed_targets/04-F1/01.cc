#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"

#include "fuzzer_temp_file.h"

using namespace Alembic::AbcGeom;
using namespace Alembic::AbcMaterial;

template <typename T>
void dumpAttributes(T const &schema) {

  const size_t meshPropertyCount = schema.getNumProperties();

  for (size_t p = 0; p < meshPropertyCount; p++) {
    const PropertyHeader &header = schema.getPropertyHeader(p);
    const PropertyType pType = header.getPropertyType();
    const std::string &name = header.getName();

    if (name == "P") {
      schema.getNumSamples();
    } else if (name == "uv" || name == "st") {
      schema.getUVsParam().getNumSamples();
    } else if (name == ".arbGeomParams") {
      // additional geometry elements (color sets, additional texture
      // coordinates)
      const ICompoundProperty geoParam = schema.getArbGeomParams();
      const size_t geoPropCount = geoParam.getNumProperties();

      for (size_t g = 0; g < geoPropCount; g++) {
        const PropertyHeader &headerGeo = geoParam.getPropertyHeader(g);
        const std::string &nameGeo = headerGeo.getName();
      }
    }
  }
}

void dumpPolyMesh(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  const IPolyMesh mesh(node.getParent(), header.getName());
  const IPolyMeshSchema &schema = mesh.getSchema();

  // Mesh properties
  dumpAttributes(schema);
}

void dumpSubD(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  const ISubD mesh(node.getParent(), header.getName());
  const ISubDSchema &schema = mesh.getSchema();

  dumpAttributes(schema);
  schema.getSubdivisionSchemeProperty();
  schema.getFaceVaryingInterpolateBoundaryProperty();
  schema.getFaceVaryingPropagateCornersProperty();
  schema.getInterpolateBoundaryProperty();
}

void dumpFaceSet(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  const IFaceSet faceSet(node.getParent(), header.getName());
  const IFaceSetSchema &schema = faceSet.getSchema();
  schema.getNumSamples();
}

void dumpCurves(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  const ICurves curves(node.getParent(), header.getName());
  const ICurvesSchema &schema = curves.getSchema();

  dumpAttributes(schema);
}

void dumpXform(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  const IXform xform(node.getParent(), header.getName());
  const IXformSchema &schema = xform.getSchema();

  schema.getNumSamples();
  schema.getNumOps();
}

void dumpMaterial(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  IMaterial material(node.getParent(), header.getName());
  IMaterialSchema &schema = material.getSchema();

  std::vector<std::string> targetNames;
  schema.getTargetNames(targetNames);

  for (const std::string &target : targetNames) {
    std::vector<std::string> shaderTypes;
    schema.getShaderTypesForTarget(target, shaderTypes);
    const size_t shaderTypeCount = shaderTypes.size();
    for (size_t s = 0; s < shaderTypeCount; s++) {

      ICompoundProperty parameters =
          schema.getShaderParameters(target, shaderTypes[s]);
      const size_t parameterCount = parameters.getNumProperties();
    }
  }
}

void dumpNodes(const IObject &node) {
  const ObjectHeader &header = node.getHeader();
  // Dump the general node information.
  header.getName();
  header.getFullName();
  header.getMetaData().serialize();

  // Dump the type specific information.
  if (IPolyMesh::matches(header)) {
    dumpPolyMesh(node);
  } else if (ISubD::matches(header)) {
    dumpSubD(node);
  } else if (IFaceSet::matches(header)) {
    dumpFaceSet(node);
  } else if (ICurves::matches(header)) {
    dumpCurves(node);
  } else if (IXform::matches(header)) {
    dumpXform(node);
  } else if (IMaterial::matches(header)) {
    dumpMaterial(node);
  } else { // Miscellaneous nodes such as the root.
    ;
  }

  // Dump the child headers.
  const size_t childCount = node.getNumChildren();
  for (size_t i = 0; i < childCount; i++) {
    dumpNodes(node.getChild(i));
  }
}

void dumpInfo(const char *file) {
  // Load the Alembic archive and verify that it is valid.
  IArchive archive(file);
  IObject root = archive.getTop();
  dumpNodes(root);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  dumpInfo(tempFile.filename());

  return 0;
}