#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Extract strings
    std::string str1 = stream.ConsumeRandomLengthString();
    char *ptr1 = const_cast<char*>(str1.c_str());
    std::string str2 = stream.ConsumeRandomLengthString();
    char *ptr2 = const_cast<char*>(str2.c_str());
    std::string str3 = stream.ConsumeRandomLengthString();
    char *ptr3 = const_cast<char*>(str3.c_str());
    std::string str4 = stream.ConsumeRandomLengthString();
    char *ptr4 = const_cast<char*>(str4.c_str());
    std::string str5 = stream.ConsumeRandomLengthString();
    char *ptr5 = const_cast<char*>(str5.c_str());
    std::string str6 = stream.ConsumeRandomLengthString();
    char *ptr6 = const_cast<char*>(str6.c_str());
    std::string str7 = stream.ConsumeRandomLengthString();
    char *ptr7 = const_cast<char*>(str7.c_str());

    // Extract integers
    int int_arg1 = stream.ConsumeIntegral<int>();
    int int_arg2 = stream.ConsumeIntegral<int>();
    int int_arg3 = stream.ConsumeIntegral<int>();
    int int_arg4 = stream.ConsumeIntegral<int>();
    int int_arg5 = stream.ConsumeIntegral<int>();

    // Initialize pointers
    struct SFTKDBHandleStr *handle1 = nullptr;
    struct SFTKDBHandleStr **handle1_ptr = &handle1;
    struct SFTKDBHandleStr *handle2 = nullptr;
    struct SFTKDBHandleStr **handle2_ptr = &handle2;

    // Call the function to fuzz
    size_t result = sftk_DBInit(ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7, int_arg1, int_arg2, int_arg3, int_arg4, int_arg5, handle1_ptr, handle2_ptr);

    return 0;
}