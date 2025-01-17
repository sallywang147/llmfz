#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "hdf5.h"

extern "C" {
#include "H5Dprivate.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::vector<uint8_t> buffer(provider.ConsumeRemainingBytes<uint8_t>());
  H5D_io_info_t io_info;
  io_info.super = nullptr;
  io_info.u.rbuf = buffer.data();
  io_info.u.rbuf_size = buffer.size();

  H5D_dset_io_info_t dset_io_info;
  dset_io_info.super = nullptr;
  dset_io_info.store_buf = nullptr;
  dset_io_info.store_buf_size = 0;
  dset_io_info.store_buf_g = nullptr;
  dset_io_info.store_buf_g_size = 0;
  dset_io_info.req_buf = nullptr;
  dset_io_info.req_buf_size = 0;
  dset_io_info.req_gbuf = nullptr;
  dset_io_info.req_gbuf_size = 0;
  dset_io_info.raw_data = nullptr;
  dset_io_info.raw_data_size = 0;
  dset_io_info.raw_gdata = nullptr;
  dset_io_info.raw_gdata_size = 0;
  dset_io_info.u.rbuf = nullptr;
  dset_io_info.u.rbuf_size = 0;
  dset_io_info.u.rbuf_g = nullptr;
  dset_io_info.u.rbuf_g_size = 0;
  dset_io_info.u.wbuf = nullptr;
  dset_io_info.u.wbuf_size = 0;
  dset_io_info.u.wbuf_g = nullptr;
  dset_io_info.u.wbuf_g_size = 0;
  dset_io_info.u.vbuf = nullptr;
  dset_io_info.u.vbuf_size = 0;
  dset_io_info.u.vbuf_g = nullptr;
  dset_io_info.u.vbuf_g_size = 0;
  dset_io_info.u.bbuf = nullptr;
  dset_io_info.u.bbuf_size = 0;
  dset_io_info.u.bbuf_g = nullptr;
  dset_io_info.u.bbuf_g_size = 0;
  dset_io_info.u.app_buf = nullptr;
  dset_io_info.u.app_buf_size = 0;
  dset_io_info.u.app_buf_g = nullptr;
  dset_io_info.u.app_buf_g_size = 0;

  H5D__virtual_read(&io_info, &dset_io_info);
  return 0;
}