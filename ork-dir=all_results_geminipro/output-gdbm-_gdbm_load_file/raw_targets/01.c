#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a dump file.
  const std::string dump_file_name = stream.ConsumeRemainingBytesAsString();
  struct dump_file dump_file;
  dump_file.name = const_cast<char*>(dump_file_name.c_str());
  dump_file.flags = 0;
  dump_file.fd = stream.ConsumeIntegral<int>();
  dump_file.buf = nullptr;
  dump_file.buf_size = 0;
  dump_file.buf_pos = 0;

  // Create a gdbm file info.
  struct gdbm_file_info dbf;
  dbf.magic = stream.ConsumeIntegral<uint32_t>();
  dbf.version = stream.ConsumeIntegral<uint16_t>();
  dbf.meta_mask = stream.ConsumeIntegral<uint16_t>();
  dbf.flags = stream.ConsumeIntegral<uint16_t>();
  dbf.nrecs = stream.ConsumeIntegral<uint32_t>();
  dbf.hdr_size = stream.ConsumeIntegral<uint32_t>();
  dbf.rec_size = stream.ConsumeIntegral<uint32_t>();
  dbf.meta_size = stream.ConsumeIntegral<uint32_t>();
  dbf.meta_data = nullptr;

  // Create an output gdbm file info.
  struct gdbm_file_info* ofp = nullptr;

  // Call the function.
  _gdbm_load_file(&dump_file, &dbf, &ofp, stream.ConsumeIntegral<int>(),
                  stream.ConsumeIntegral<int>());

  return 0;
}