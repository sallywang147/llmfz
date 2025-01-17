#include <fuzzer/FuzzedDataProvider.h>
#include <libexif/exif-data.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a temporary file and write the data into it.
    char filename[] = "/tmp/fuzz-XXXXXX";
    int fd = mkstemp(filename);
    if (fd < 0) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    std::string str = stream.ConsumeRemainingBytesAsString();
    fwrite(str.data(), 1, str.size(), file);
    fclose(file);

    // Now we can call the function.
    ExifData *exifData = exif_data_new_from_file(filename);

    // Clean up.
    if (exifData) {
        exif_data_unref(exifData);
    }
    remove(filename);

    return 0;
}