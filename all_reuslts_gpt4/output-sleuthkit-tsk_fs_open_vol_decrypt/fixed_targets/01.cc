#include <fuzzer/FuzzedDataProvider.h>
#include <tsk/libtsk.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Creating a dummy TSK_VS_PART_INFO object
    TSK_VS_PART_INFO a_part_info;
    a_part_info.addr = stream.ConsumeIntegral<uint8_t>();
    a_part_info.start = stream.ConsumeIntegral<uint32_t>();
    a_part_info.len = stream.ConsumeIntegral<uint32_t>();
    a_part_info.flags = (TSK_VS_PART_FLAG_ENUM)stream.ConsumeIntegral<uint8_t>();
    a_part_info.table_num = stream.ConsumeIntegral<uint8_t>();
    a_part_info.slot_num = stream.ConsumeIntegral<uint8_t>();

    // Creating a dummy a_ftype
    int a_ftype = stream.ConsumeIntegral<int>();

    // Creating a dummy a_pass
    std::string a_pass = stream.ConsumeRandomLengthString();
    
    // Call the function to fuzz
    TSK_FS_INFO *fs_info = tsk_fs_open_vol_decrypt(&a_part_info, a_ftype, const_cast<char*>(a_pass.c_str()));

    if (fs_info != nullptr) {
        tsk_fs_close(fs_info);
    }

    return 0;
}