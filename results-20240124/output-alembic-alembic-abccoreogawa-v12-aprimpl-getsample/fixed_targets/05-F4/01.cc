#include <iostream>
#include <vector>

#include <Alembic/AbcGeom/IPolyMesh.h>

using namespace Alembic::AbcGeom;

class MyPolyMesh : public IPolyMesh {
public:
  MyPolyMesh(const ObjectHeader &header, const Abc::Argument &args)
      : IPolyMesh(header, args) {}

  bool matches(const ObjectHeader &header) const override {
    return true;
  }

  void getSchemaObject(Abc::IObject &parent, Abc::CompoundPropertyWriterPtr &propWriter,
                       bool isWrite) const override {}

  void getSelfBounds(Box3d &box, const SampleSelector &sampleIndex) const override {}

  void getFaceIndices(std::vector<int32_t> &indices, const SampleSelector &sampleIndex) const override {}

  void getFaceCounts(std::vector<int32_t> &counts, const SampleSelector &sampleIndex) const override {}

  void getPositions(std::vector<V3f> &positions, const SampleSelector &sampleIndex) const override {}

  void getNormals(std::vector<V3f> &normals, const SampleSelector &sampleIndex) const override {}

  void getUVs(std::vector<V2f> &uvs, const SampleSelector &sampleIndex) const override {}

  void getColors(std::vector<C3f> &colors, const SampleSelector &sampleIndex) const override {}
};

extern "C" {
#include <Alembic/AbcCoreOgawa/v12/AprImpl.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Alembic::AbcCoreOgawa::v12::AprImpl impl;
  std::shared_ptr<Alembic::AbcGeom::IPolyMesh> polyMesh;
  impl.getSample(&polyMesh, size, &data);
}

int main() {
  return 0;
}