#include <fuzzer/FuzzedDataProvider.h>
#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyobj::material_t material1;
  material1.ambient[0] = stream.ConsumeFloatingPoint<double>();
  material1.ambient[1] = stream.ConsumeFloatingPoint<double>();
  material1.ambient[2] = stream.ConsumeFloatingPoint<double>();
  
  material1.diffuse[0] = stream.ConsumeFloatingPoint<double>();
  material1.diffuse[1] = stream.ConsumeFloatingPoint<double>();
  material1.diffuse[2] = stream.ConsumeFloatingPoint<double>();
  
  material1.specular[0] = stream.ConsumeFloatingPoint<double>();
  material1.specular[1] = stream.ConsumeFloatingPoint<double>();
  material1.specular[2] = stream.ConsumeFloatingPoint<double>();
  
  material1.transmittance[0] = stream.ConsumeFloatingPoint<double>();
  material1.transmittance[1] = stream.ConsumeFloatingPoint<double>();
  material1.transmittance[2] = stream.ConsumeFloatingPoint<double>();
  
  material1.emission[0] = stream.ConsumeFloatingPoint<double>();
  material1.emission[1] = stream.ConsumeFloatingPoint<double>();
  material1.emission[2] = stream.ConsumeFloatingPoint<double>();
  
  material1.shininess = stream.ConsumeFloatingPoint<double>();
  material1.ior = stream.ConsumeFloatingPoint<double>();
  
  material1.dissolve = stream.ConsumeFloatingPoint<double>();
  material1.illum = stream.ConsumeIntegral<int>();
  
  material1.ambient_texname = stream.ConsumeRandomLengthString();
  material1.diffuse_texname = stream.ConsumeRandomLengthString();
  material1.specular_texname = stream.ConsumeRandomLengthString();
  material1.normal_texname = stream.ConsumeRandomLengthString();
  material1.alpha_texname = stream.ConsumeRandomLengthString();

  tinyobj::material_t material2(material1);

  return 0;
}