#include <allheaders.h>
#include <tesseract/baseapi.h>
#include <tesseract/renderer.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdio>  // for printf
#include <cstdlib> // for std::getenv, std::setenv
#include <libgen.h> // for dirname
#include <string>  // for std::string

class BitReader {
private:
  uint8_t const *data;
  size_t size;
  size_t shift;

public:
  BitReader(const uint8_t *data, size_t size) : data(data), size(size), shift(0) {}

  int Read(void) {
    if (size == 0) {
      return 0;
    }

    const int ret = ((*data) >> shift) & 1;

    shift++;
    if (shift >= 8) {
      shift = 0;
      data++;
      size--;
    }

    return ret;
  }
};

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

  std::string filename = stream.ConsumeRandomLengthString();
  std::string retry_config = stream.ConsumeRandomLengthString();
  int timeout_millisec = stream.ConsumeIntegral<int>();
  tesseract::TessResultRenderer *renderer = nullptr;

  api->ProcessPages(filename.c_str(), retry_config.c_str(), timeout_millisec, renderer);

  return 0;
}