#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t n = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t m = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t p = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t q = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t r = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t s = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t t = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t u = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t v = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t w = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t x = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t y = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t z = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t a = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t b = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t c = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t d = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t e = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t f = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t g = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t h = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t i = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t j = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t k = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t l = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t o = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ii = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t jj = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t kk = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ll = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t mm = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t nn = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t oo = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t pp = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t qq = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t rr = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ss = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t tt = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t uu = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t vv = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ww = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t xx = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t yy = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t zz = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t aaa = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t bbb = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ccc = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ddd = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t eee = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t fff = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ggg = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t hhh = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t iii = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t jjj = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t kkk = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t lll = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t mmm = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t nnn = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ooo = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ppp = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t qqq = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t rrr = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t sss = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ttt = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t uuu = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t vvv = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t www = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t xxx = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t yyy = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t zzz = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t aaaa = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t bbbb = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t cccc = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t dddd = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t eeee = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t ffff = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t gggg = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  size_t hhhh = provider.