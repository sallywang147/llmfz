#include <stddef.h>
#include <stdint.h>

#include "sleuthkit/tsk/fs/tsk_fs.h"
#include "sleuthkit/tsk/tsk_tools_i.h"
#include "sleuthkit_mem_img.h"

extern "C" {
#include "sleuthkit/tsk/tsk_img_i.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TSK_IMG_INFO *img;
  TSK_VS_PART_INFO *part;
  TSK_FS_INFO *fs;

  img = mem_open(data, size);
  if (img == nullptr) {
    return 0;
  }
  part = tsk_vs_part_get(img, 0);

  if (part == nullptr) {
    goto out_img;
  }
  fs = tsk_fs_open_vol_decrypt(part, TSK_FS_TYPE_DETECT, "");

  if (fs != nullptr) {
    tsk_fs_fls(fs, TSK_FS_FLS_FULL, fs->root_inum, TSK_FS_DIR_WALK_FLAG_RECURSE, nullptr, 0);

    fs->close(fs);
  }
  tsk_vs_part_close(part);

out_img:
  tsk_img_close(img);

  return 0;
}
```

The build error message is:
```
error: ‘tsk_fs_close’ was not declared in this scope
```

This error occurs because the `tsk_fs_close` function is declared in the `tsk_fs.h` header file, which is not included in the code. To fix this error, add the following line to the beginning of the code:
```
#include "sleuthkit/tsk/fs/tsk_fs.h"
```

After adding this line, the code should compile and run without errors.