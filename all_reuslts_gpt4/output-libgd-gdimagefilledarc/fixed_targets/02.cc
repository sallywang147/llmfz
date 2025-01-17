#include <fuzzer/FuzzedDataProvider.h>
#include <gd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    FuzzedDataProvider stream(data, size);

    const int width = 100;
    const int height = 100;
    gdImagePtr im = gdImageCreateTrueColor(width, height);
    if (!im) {
        return 0;
    }

    int cx = stream.ConsumeIntegralInRange<int>(0, width);
    int cy = stream.ConsumeIntegralInRange<int>(0, height);
    int w = stream.ConsumeIntegralInRange<int>(0, width);
    int h = stream.ConsumeIntegralInRange<int>(0, height);
    int s = stream.ConsumeIntegralInRange<int>(0, 360);
    int e = stream.ConsumeIntegralInRange<int>(0, 360);
    int color = stream.ConsumeIntegral<int>();
    int style = stream.ConsumeIntegral<int>();

    gdImageFilledArc(im, cx, cy, w, h, s, e, color, style);

    gdImageDestroy(im);

    return 0;
}