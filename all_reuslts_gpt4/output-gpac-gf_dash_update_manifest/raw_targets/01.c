#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/dash.h>
#include <gpac/network.h>
#include <gpac/internal/dash.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize the DASH client
    GF_DASHFileIO dash_io;
    memset(&dash_io, 0, sizeof(GF_DASHFileIO));
    GF_DASHClient *dash = gf_dash_new(&dash_io, 0, 0, 0);

    // Create a temporary manifest file
    char filename[256];
    sprintf(filename, "/tmp/libfuzzer.%d", getpid());

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        gf_dash_del(dash);
        return 0;
    }

    std::string manifest = stream.ConsumeRemainingBytesAsString();
    fwrite(manifest.c_str(), 1, manifest.size(), fp);
    fclose(fp);

    // Set the manifest name in the DASH client
    gf_dash_set_manifest_name(dash, filename);

    // Call the target function
    int result = gf_dash_update_manifest(dash);

    // Clean up
    unlink(filename);
    gf_dash_del(dash);

    return 0;
}