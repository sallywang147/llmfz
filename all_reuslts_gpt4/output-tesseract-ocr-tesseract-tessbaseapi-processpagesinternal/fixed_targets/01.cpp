#include <allheaders.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdio>   // for printf
#include <cstdlib>  // for std::getenv, std::setenv
#include <libgen.h> // for dirname
#include <string>   // for std::string

static tesseract::TessBaseAPI *api = nullptr;

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

  api = new tesseract::TessBaseAPI();
  if (api->Init(nullptr, "eng") != 0) {
    printf("Cannot initialize API\n");
    abort();
  }

  /* Silence output */
  api->SetVariable("debug_file", "/dev/null");

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string for filename. You MUST use .c_str() to use result as pointer
  std::string filename = stream.ConsumeRandomLengthString();
  char *filename_ptr = const_cast<char*>(filename.c_str());

  // Extract a string for retry_config. You MUST use .c_str() to use result as pointer
  std::string retry_config = stream.ConsumeRandomLengthString();
  char *retry_config_ptr = const_cast<char*>(retry_config.c_str());

  // Extract integral values for timeout_millisec
  int timeout_millisec = stream.ConsumeIntegral<int>();

  // Create a TessResultRenderer object
  tesseract::TessResultRenderer* renderer = new tesseract::TessTextRenderer();

  // Call the function to fuzz
  api->ProcessPagesInternal(filename_ptr, retry_config_ptr, timeout_millisec, renderer);

  delete renderer;

  return 0;
}