#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "futils.h"
#include "git2.h"

#include "standalone_driver.h"

#define UNUSED(x) (void)(x)

int LLVMFuzzerInitialize(int *argc, char ***argv) {
#if defined(_WIN32)
  char tmpdir[MAX_PATH], path[MAX_PATH];

  if (GetTempPath((DWORD)sizeof(tmpdir), tmpdir) == 0)
    abort();

  if (GetTempFileName(tmpdir, "lg2", 1, path) == 0)
    abort();

  if (git_futils_mkdir(path, 0700, 0) < 0)
    abort();
#else
  char path[] = "/tmp/git2.XXXXXX";

  if (mkdtemp(path) != path)
    abort();
#endif

  if (git_libgit2_init() < 0)
    abort();

  if (git_libgit2_opts(GIT_OPT_SET_PACK_MAX_OBJECTS, 10000000) < 0)
    abort();

  UNUSED(argc);
  UNUSED(argv);

  return 0;
}

int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  struct fuzzer_buffer buffer = {data, size};
  git_clone_options options = GIT_CLONE_OPTIONS_INIT;
  git_repository *repo;

  if (git_clone(&repo, (char *)buffer.data, path, &options) < 0)
    goto out;

  git_repository_free(repo);

out:
  return 0;
}