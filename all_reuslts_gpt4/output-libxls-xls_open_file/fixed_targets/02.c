#include <fuzzer/FuzzedDataProvider.h>
#include "xls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Prepare a temporary file to write the fuzzing input.
  char file_path[] = "/tmp/fuzzing_input.XXXXXX";
  int fd = mkstemp(file_path);
  if (fd < 0) {
    return 0;
  }

  // Write the data to the temporary file.
  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  write(fd, buffer.data(), buffer.size());
  close(fd);

  // Call the function to fuzz.
  int outError = 0;
  struct xlsWorkBook *workBook = xls_open_file(file_path, "UTF-8", &outError);

  // Clean up.
  if (workBook != nullptr) {
    xls_close_WB(workBook);
  }
  remove(file_path);

  return 0;
}