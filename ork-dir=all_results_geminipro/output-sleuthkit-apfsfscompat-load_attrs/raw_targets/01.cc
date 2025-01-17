#include <stddef.h>
#include <stdint.h>

#include "apfs_compat.h"
#include "tsk/fs/tsk_fs_i.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  APFSFSCompat *apfs_compat = new APFSFSCompat();
  if (apfs_compat == nullptr) {
    return 0;
  }
  TSK_FS_INFO *fs_info = nullptr;
  TSK_FS_FILE *fs_file = nullptr;

  apfs_compat->load_attrs(apfs_compat, fs_file);

  delete apfs_compat;

  return 0;
}