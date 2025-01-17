#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include "proj.h"
}

/* Standalone build:
g++ -g -std=c++11 proj_get_suggested_operation_fuzzer.cpp -o proj_get_suggested_operation_fuzzer
-fvisibility=hidden -DSTANDALONE ../../build/lib/libproj.a -lpthread -lsqlite3
-I../../src -I../../include
*/

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv);
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len);

extern "C" {
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

  FuzzedDataProvider stream(buf, len);
  struct PJ_OBJ_LIST *obj_list = proj_create_obj_list();
  union PJ_COORD coord;
  coord.xy.x = stream.ConsumeIntegral<double>();
  coord.xy.y = stream.ConsumeIntegral<double>();
  coord.xy.z = stream.ConsumeIntegral<double>();

  int ret = proj_get_suggested_operation(nullptr, obj_list, 0, &coord);
  proj_destroy_obj_list(obj_list);
  proj_cleanup();
  return ret;
}
} // extern "C"

#ifdef STANDALONE

int main(int argc, char *argv[]) {
  if (argc < 2) {
    const char str[] = "1.0 2.0 3.0";
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