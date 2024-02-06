#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "tiny_obj_loader.h"

static void vertex_cb(void *user_data, float x, float y, float z, float w) {
  // Do nothing.
}

static void normal_cb(void *user_data, float x, float y, float z) {
  // Do nothing.
}

static void texcoord_cb(void *user_data, float x, float y, float z) {
  // Do nothing.
}

static void index_cb(void *user_data, tinyobj::index_t *indices, int num_indices) {
  // Do nothing.
}

static void usemtl_cb(void *user_data, const char *name, int material_id) {
  // Do nothing.
}

static void mtllib_cb(void *user_data, const tinyobj::material_t *materials, int num_materials) {
  // Do nothing.
}

static void group_cb(void *user_data, const char **names, int num_names) {
  // Do nothing.
}

static void object_cb(void *user_data, const char *name) {
  // Do nothing.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  std::istringstream inStream(str);

  tinyobj::callback_t callback;
  callback.vertex_cb = vertex_cb;
  callback.normal_cb = normal_cb;
  callback.texcoord_cb = texcoord_cb;
  callback.index_cb = index_cb;
  callback.usemtl_cb = usemtl_cb;
  callback.mtllib_cb = mtllib_cb;
  callback.group_cb = group_cb;
  callback.object_cb = object_cb;

  char user_data[1] = {0};
  std::exception readMatFn;
  std::string warn;
  std::string err;

  tinyobj::LoadObjWithCallback(&inStream, &callback, user_data, &readMatFn, &warn, &err);

  return 0;
}