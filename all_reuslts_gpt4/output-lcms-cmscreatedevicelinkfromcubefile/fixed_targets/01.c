#include <fuzzer/FuzzedDataProvider.h>
#include <lcms2.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    std::string filename = stream.ConsumeRandomLengthString();
    char *cFileName = const_cast<char *>(filename.c_str());

    char *deviceLink = cmsCreateDeviceLinkFromCubeFile(cFileName);
    if (deviceLink != nullptr) {
        cmsCloseProfile(deviceLink);
    }

    return 0;
}