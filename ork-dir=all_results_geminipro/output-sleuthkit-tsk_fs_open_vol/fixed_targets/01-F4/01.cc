#include <stddef.h>
#include <stdint.h>

#include "sleuthkit/tsk/fs/tsk_fs.h"
#include "sleuthkit/tsk/pool/tsk_pool.h"
#include "sleuthkit/tsk/tsk_tools_i.h"
#include "sleuthkit/tsk/tsk_img.h"
#include "sleuthkit_mem_img.h"

extern "C" {
#include "sleuthkit/tsk/tsk_img_i.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TSK_IMG_INFO *img;
  TSK_FS_INFO *fs;
  TSK_VS_PART_INFO *part;
  TSK_POOL_INFO *pool;

  img = mem_open(data, size);
  if (img == nullptr) {
    return 0;
  }
  pool = tsk_pool_open_img_sing(img, 0, TSK_POOL_TYPE_RAW);

  if (pool == nullptr) {
    goto out_img;
  }
  part = tsk_vs_part_get(pool, 0);

  if (part == nullptr) {
    goto out_pool;
  }
  fs = tsk_fs_open_vol(part, TSK_FS_TYPE_DETECT);

  if (fs != nullptr) {
    tsk_fs_fls(fs, TSK_FS_FLS_FULL, fs->root_inum, TSK_FS_DIR_WALK_FLAG_RECURSE, nullptr, 0);

    tsk_fs_close(fs);  // Fix: Use the correct close function for TSK_FS_INFO
  }
  tsk_vs_part_close(part);

out_pool:
  tsk_pool_close(pool);

out_img:
  tsk_img_close(img);

  return 0;
}