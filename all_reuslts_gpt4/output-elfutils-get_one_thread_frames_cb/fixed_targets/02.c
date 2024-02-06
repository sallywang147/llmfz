#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <libdwfl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize libdwfl
    static const Dwfl_Callbacks offline_callbacks = {
        .find_debuginfo = dwfl_standard_find_debuginfo,
        .section_address = dwfl_offline_section_address,
    };
    Dwfl *dwfl = dwfl_begin(&offline_callbacks);
    if (dwfl == NULL) {
        return 0;
    }

    // Create a temporary file
    char filename[] = "/tmp/fuzz-dwfl.XXXXXX";
    int fd = mkstemp(filename);
    assert(fd >= 0);

    // Write the fuzzing input into the temporary file
    std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
    write(fd, bytes.data(), bytes.size());
    close(fd);

    // Report the temporary file to libdwfl
    Dwfl_Module *mod = dwfl_report_offline(dwfl, "fuzz", filename, -1);
    if (mod == NULL) {
        unlink(filename);
        dwfl_end(dwfl);
        return 0;
    }

    dwfl_report_end(dwfl, NULL, NULL);

    // Initialize a Dwfl_Thread for the callback
    Dwfl_Thread thread = { .dwfl = dwfl, .tid = 1 };

    // Consume a string for the callback argument
    std::string arg = stream.ConsumeRandomLengthString();

    // Call the function to fuzz
    get_one_thread_frames_cb(&thread, const_cast<char *>(arg.c_str()));

    // Clean up
    unlink(filename);
    dwfl_end(dwfl);

    return 0;
}