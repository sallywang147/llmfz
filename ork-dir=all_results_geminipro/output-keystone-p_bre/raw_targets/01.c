#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

struct parse {
  int a;
  int b;
  int c;
};

void p_bre(struct parse* p, int x, int y) {
  p->a = x;
  p->b = y;
  p->c = x + y;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct parse p;
  p.a = stream.ConsumeIntegral<int>();
  p.b = stream.ConsumeIntegral<int>();
  p_bre(&p, p.a, p.b);
  return 0;
}