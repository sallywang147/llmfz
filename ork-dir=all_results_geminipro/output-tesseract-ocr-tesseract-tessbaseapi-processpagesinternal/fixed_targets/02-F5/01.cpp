#include <allheaders.h>
#include <tesseract/baseapi.h>

#include <cstdio>   // for printf
#include <cstdlib>  // for std::getenv, std::setenv
#include <libgen.h> // for dirname
#include <string>   // for std::string

#ifndef TESSERACT_FUZZER_WIDTH
#define TESSERACT_FUZZER_WIDTH 100
#endif

#ifndef TESSERACT_FUZZER_HEIGHT
#define TESSERACT_FUZZER_HEIGHT 100
#endif

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
  BitReader BR(data, size);

  auto pix = createPix(BR, TESSERACT_FUZZER_WIDTH, TESSERACT_FUZZER_HEIGHT);

  api->SetImage(pix);

  api->ProcessPagesInternal(nullptr, nullptr, 0, nullptr);

  pixDestroy(&pix);

  return 0;
}

int main(int argc, char **argv) {
  // Initialize the Tesseract API.
  api->Init(nullptr, "eng");

  // Set the debug file to /dev/null to silence output.
  api->SetVariable("debug_file", "/dev/null");

  // Create a BitReader object to read the input data.
  BitReader BR(argv[1], argc - 1);

  // Create a Pix object from the input data.
  auto pix = createPix(BR, TESSERACT_FUZZER_WIDTH, TESSERACT_FUZZER_HEIGHT);

  // Set the image to the Tesseract API.
  api->SetImage(pix);

  // Process the image and extract the text.
  api->ProcessPagesInternal(nullptr, nullptr, 0, nullptr);

  // Destroy the Pix object.
  pixDestroy(&pix);

  // Get the extracted text.
  const char *text = api->GetUTF8Text();

  // Print the extracted text.
  printf("%s\n", text);

  // Destroy the Tesseract API.
  api->End();

  return 0;
}