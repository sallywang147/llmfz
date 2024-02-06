#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "proj.h"

/* Standalone build:
g++ -g -std=c++11 proj_get_suggested_operation_fuzzer.cpp -o proj_get_suggested_operation_fuzzer
-fvisibility=hidden -DSTANDALONE ../../build/lib/libproj.a -lpthread -lsqlite3
-I../../src -I../../include
*/

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv);
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len);

int LLVMFuzzerInitialize(int * /*argc*/, char ***argv) {
  const char *argv0 = (*argv)[0];
  char *path = strdup(argv0);
  char *lastslash = strrchr(path, '/');
  if (lastslash) {
    *lastslash = '\0';
    setenv("PROJ_DATA", path, 1);
  } else {
    setenv("PROJ_DATA", ".", 1);
  }
  free(path);
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  if (len > 1000) {
#ifdef STANDALONE
    fprintf(stderr, "Input too large\n");
#endif
    return -1;
  }

  /* We expect the blob to be 2 lines: */
  /* source_string\ndestination_string */
  char *buf_dup = (char *)malloc(len + 1);
  memcpy(buf_dup, buf, len);
  buf_dup[len] = 0;
  char *first_line = buf_dup;
  char *first_newline = strchr(first_line, '\n');
  if (!first_newline) {
    free(buf_dup);
    return -1;
  }
  first_newline[0] = 0;
  char *second_line = first_newline + 1;

#ifdef STANDALONE
  fprintf(stderr, "src=%s\n", first_line);
  fprintf(stderr, "dst=%s\n", second_line);
#endif

  proj_destroy(proj_create_crs_to_crs(nullptr, first_line, second_line, nullptr));

  free(buf_dup);
  proj_cleanup();
  return 0;
}

#ifdef STANDALONE

int main(int argc, char *argv[]) {
  if (argc < 2) {
    const char str[] = "+proj=longlat +datum=WGS84 +nodefs\n+proj=longlat "
                       "+datum=WGS84 +nodefs";
    int ret = LLVMFuzzerTestOneInput((const uint8_t *)(str), sizeof(str) - 1);
    if (ret)
      return ret;

    return 0;
  } else {
    int nRet = 0;
    void *buf = NULL;
    int nLen = 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
      fprintf(stderr, "%s does not exist.\n", argv[1]);
      exit(1);
    }
    fseek(f, 0, SEEK_END);
    nLen = (int)ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc(nLen);
    if (!buf) {
      fprintf(stderr, "malloc failed.\n");
      fclose(f);
      exit(1);
    }
    if (fread(buf, nLen, 1, f) != 1) {
      fprintf(stderr, "fread failed.\n");
      fclose(f);
      free(buf);
      exit(1);
    }
    fclose(f);
    nRet = LLVMFuzzerTestOneInput((const uint8_t *)(buf), nLen);
    free(buf);
    return nRet;
  }
}

#endif // STANDALONE