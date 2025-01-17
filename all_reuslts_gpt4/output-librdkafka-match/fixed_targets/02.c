#include <fuzzer/FuzzedDataProvider.h>
#include "regexp.h"

struct Reinst {
  int type; /* Instruction: CHAR,.,^,$,*,+,?, and or */
  char ch;  /* if type==CHAR */
  char *sp; /* [sic] */
  char *ep; /* [sic] */
  struct Reinst *next; /* for * + and ? */
  struct Reinst *left; /* tree structure */
  struct Reinst *right; /* tree structure */
};

struct Resub {
  char *sp;
  char *ep;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  if (size < 2)
    return 0;

  struct Reinst pc;
  struct Resub out;

  pc.type = stream.ConsumeIntegral<int>();
  pc.ch = stream.ConsumeIntegral<char>();
  std::string sp_str = stream.ConsumeRemainingBytesAsString();
  pc.sp = (char *)sp_str.c_str();
  pc.ep = pc.sp + sp_str.size();
  pc.next = NULL;
  pc.left = NULL;
  pc.right = NULL;

  char *sp = pc.sp;
  char *bol = pc.sp;
  int flags = stream.ConsumeIntegral<int>();

  match(&pc, sp, bol, flags, &out);

  return 0;
}