#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int mz_zip_add_mem_to_archive_file_in_place(char * , char * , char * , size_t , char * , short , int );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string archive_name = stream.ConsumeRandomLengthString();
  std::string archive_comment = stream.ConsumeRandomLengthString();
  std::string file_name = stream.ConsumeRandomLengthString();
  std::string file_comment = stream.ConsumeRandomLengthString();

  size_t file_size = stream.ConsumeIntegral<size_t>();
  short level = stream.ConsumeIntegral<short>();
  int zip_flags = stream.ConsumeIntegral<int>();

  std::vector<char> file_data = stream.ConsumeRemainingBytes<char>();

  mz_zip_add_mem_to_archive_file_in_place(
      const_cast<char*>(archive_name.c_str()),
      const_cast<char*>(archive_comment.c_str()),
      const_cast<char*>(file_name.c_str()),
      file_size,
      file_data.data(),
      level,
      zip_flags
  );

  return 0;
}