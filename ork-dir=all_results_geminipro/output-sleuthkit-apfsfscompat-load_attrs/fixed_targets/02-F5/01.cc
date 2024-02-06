#include <stddef.h>
#include <stdint.h>

#include "sleuthkit/tsk/fs/apfs/apfs_fs.h"
#include "sleuthkit/tsk/fs/tsk_fs.h"
#include "sleuthkit/tsk/pool/tsk_pool.h"
#include "sleuthkit/tsk/tsk_tools_i.h"
#include "sleuthkit_mem_img.h"

extern "C" {
#include <sleuthkit/tsk/fs/apfs/apfs_fs_attr.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TSK_IMG_INFO *img;
  TSK_IMG_INFO *pool_img;
  TSK_FS_INFO *fs;
  const TSK_POOL_INFO *pool;
  TSK_FS_FILE *file;

  img = mem_open(data, size);
  if (img == nullptr) {
    return 0;
  }
  pool = tsk_pool_open_img_sing(img, 0, TSK_POOL_TYPE_APFS);

  if (pool == nullptr) {
    goto out_img;
  }
  // Pool start block is APFS container specific and is hard coded for now
  pool_img = pool->get_img_info(pool, (TSK_DADDR_T)106);

  if (pool_img == nullptr) {
    goto out_pool;
  }
  fs = tsk_fs_open_img_decrypt(pool_img, 0, TSK_FS_TYPE_APFS_DETECT, "");

  if (fs == nullptr) {
    goto out_pool_img;
  }
  file = tsk_fs_file_open(fs, 1);
  if (file == nullptr) {
    goto out_fs;
  }

  APFSFSCompat *apfs_fs = (APFSFSCompat *)fs;
  char ret = apfs_fs->load_attrs(apfs_fs, file);

  tsk_fs_file_close(file);

out_fs:
  tsk_fs_close(fs);

out_pool_img:
  tsk_img_close(pool_img);

out_pool:
  tsk_pool_close(pool);

out_img:
  tsk_img_close(img);

  return 0;
}