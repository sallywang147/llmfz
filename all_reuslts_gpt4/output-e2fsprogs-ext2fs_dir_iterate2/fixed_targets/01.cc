#include <fuzzer/FuzzedDataProvider.h>
#include <ext2fs/ext2fs.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    // Initialize the filesystem
    ext2_filsys fs;
    memset(&fs, 0, sizeof(fs));

    // Consume data for parameters
    int dir = stream.ConsumeIntegral<int>();
    int flags = stream.ConsumeIntegral<int>();
    std::string block_buf = stream.ConsumeBytesAsString(stream.remaining_bytes());

    // Define the function to be used for iteration
    int (*func)(struct ext2_dir_entry *dirent, int offset, int blocksize, char *buf, void *priv_data);
    func = [](struct ext2_dir_entry *dirent, int offset, int blocksize, char *buf, void *priv_data) -> int {
        return 0; // Just return 0 for simplicity
    };

    // Call the function
    ext2fs_dir_iterate2(&fs, dir, flags, block_buf.data(), func, nullptr);

    return 0;
}