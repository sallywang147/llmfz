#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/compositor.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  GF_Compositor *compositor = gf_sc_new(NULL, 0, NULL, NULL);
  if (!compositor) {
    return 0;
  }

  std::string type = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string com = stream.ConsumeRemainingBytesAsString();

  gf_sc_scene_update(compositor, (char *)type.c_str(), (char *)com.c_str());

  gf_sc_del(compositor);

  return 0;
}