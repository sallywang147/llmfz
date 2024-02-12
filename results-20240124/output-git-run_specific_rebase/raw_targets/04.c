 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "rebase.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct rebase_options options;
  options.verbose = stream.ConsumeBool();
  options.quiet = stream.ConsumeBool();
  options.force = stream.ConsumeBool();
  options.test = stream.ConsumeBool();
  options.allow_conflicts = stream.ConsumeBool();
  options.allow_empty = stream.ConsumeBool();
  options.allow_missing = stream.ConsumeBool();
  options.allow_unresolved = stream.ConsumeBool();
  options.allow_insecure = stream.ConsumeBool();
  options.allow_unsafe = stream.ConsumeBool();
  options.allow_symlinks = stream.ConsumeBool();
  options.allow_hardlinks = stream.ConsumeBool();
  options.allow_other_mounts = stream.ConsumeBool();
  options.allow_loopback_mounts = stream.ConsumeBool();
  options.allow_non_root = stream.ConsumeBool();
  options.allow_root_squash = stream.ConsumeBool();
  options.allow_no_root_squash = stream.ConsumeBool();
  options.allow_root_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dir = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_fs = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_mount = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_inode = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_flags = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uid = stream.ConsumeIntegral<uid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_gid = stream.ConsumeIntegral<gid_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mode = stream.ConsumeIntegral<mode_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_rdev = stream.ConsumeIntegral<dev_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ino = stream.ConsumeIntegral<ino_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_nlink = stream.ConsumeIntegral<nlink_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_size = stream.ConsumeIntegral<off_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_blocks = stream.ConsumeIntegral<blkcnt_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_atime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_mtime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_ctime = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_major = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_minor = stream.ConsumeIntegral<int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_type = stream.ConsumeIntegral<unsigned int>();
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_name = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_type = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_uuid = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_label = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_options = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_point = stream.ConsumeBytesAsString(
      stream.ConsumeIntegralInRange(0, 1024));
  options.allow_root_dev_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_fs_mount_time = stream.ConsumeIntegral<time_t>();
  options.allow_root_dev_fs