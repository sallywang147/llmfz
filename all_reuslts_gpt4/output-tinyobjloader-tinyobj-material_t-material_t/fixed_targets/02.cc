#include <fuzzer/FuzzedDataProvider.h>
#include <tiny_obj_loader.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  tinyobj::material_t material1;
  material1.ambient[0] = provider.ConsumeFloatingPoint<double>();
  material1.ambient[1] = provider.ConsumeFloatingPoint<double>();
  material1.ambient[2] = provider.ConsumeFloatingPoint<double>();
  
  material1.diffuse[0] = provider.ConsumeFloatingPoint<double>();
  material1.diffuse[1] = provider.ConsumeFloatingPoint<double>();
  material1.diffuse[2] = provider.ConsumeFloatingPoint<double>();
  
  material1.specular[0] = provider.ConsumeFloatingPoint<double>();
  material1.specular[1] = provider.ConsumeFloatingPoint<double>();
  material1.specular[2] = provider.ConsumeFloatingPoint<double>();
  
  material1.transmittance[0] = provider.ConsumeFloatingPoint<double>();
  material1.transmittance[1] = provider.ConsumeFloatingPoint<double>();
  material1.transmittance[2] = provider.ConsumeFloatingPoint<double>();
  
  material1.emission[0] = provider.ConsumeFloatingPoint<double>();
  material1.emission[1] = provider.ConsumeFloatingPoint<double>();
  material1.emission[2] = provider.ConsumeFloatingPoint<double>();
  
  material1.shininess = provider.ConsumeFloatingPoint<double>();
  material1.ior = provider.ConsumeFloatingPoint<double>();
  material1.dissolve = provider.ConsumeFloatingPoint<double>();
  material1.illum = provider.ConsumeIntegral<int>();
  
  material1.ambient_texname = provider.ConsumeRandomLengthString();
  material1.diffuse_texname = provider.ConsumeRandomLengthString();
  material1.specular_texname = provider.ConsumeRandomLengthString();
  material1.specular_highlight_texname = provider.ConsumeRandomLengthString();
  material1.bump_texname = provider.ConsumeRandomLengthString();
  material1.displacement_texname = provider.ConsumeRandomLengthString();
  material1.alpha_texname = provider.ConsumeRandomLengthString();
  
  tinyobj::material_t material2(material1);

  return 0;
}