#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <mntent.h>

extern "C" {
int mnt_table_parse_fstab(const char* path, struct mnttab* mtab);
void mnt_init_table(struct mnttab* mtab, int size);
void mnt_free_table(struct mnttab* mtab);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  struct mnttab mtab;
  struct mntent* mnt;
  mnt_init_table(&mtab, 10);
  FILE* fp = setmntent("/etc/fstab", "r");
  if (fp == nullptr) {
    return 0;
  }

  while ((mnt = getmntent(fp)) != nullptr) {
    if (mnt->mnt_type != nullptr && strcmp(mnt->mnt_type, "fuseblk") == 0) {
      printf("Found a fuseblk mount: %s\n", mnt->mnt_dir);
    }
  }

  endmntent(fp);
  mnt_free_table(&mtab);
  return 0;
}