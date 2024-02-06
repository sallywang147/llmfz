#include <tesseract/baseapi.h>
#include <tesseract/tsvrenderer.h>

#include <cstdio>   // for printf
#include <cstdlib>  // for std::getenv, std::setenv
#include <libgen.h> // for dirname
#include <string>   // for std::string

extern "C" int LLVMFuzzerInitialize(int * /*pArgc*/, char ***pArgv) {
  if (std::getenv("TESSDATA_PREFIX") == nullptr) {
    std::string binary_path = *pArgv[0];
    const std::string filepath = dirname(&binary_path[0]);

    const std::string tessdata_path = filepath + "/" + "tessdata";
    if (setenv("TESSDATA_PREFIX", tessdata_path.c_str(), 1) != 0) {
      printf("Setenv failed\n");
      std::abort();
    }
  }

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  if (api->Init(nullptr, "eng") != 0) {
    printf("Cannot initialize API\n");
    abort();
  }

  /* Silence output */
  api->SetVariable("debug_file", "/dev/null");

  tesseract::TessTsvRenderer *tsvRenderer = new tesseract::TessTsvRenderer();
  tsvRenderer->AddImageHandler(api);

  delete api;
  delete tsvRenderer;

  return 0;
}