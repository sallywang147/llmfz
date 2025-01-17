#include <fuzzer/FuzzedDataProvider.h>
#include <avahi-common/strlst.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create an empty AvahiStringList
    struct AvahiStringList *strList = NULL;

    // Consume the data as a string to use as the format string
    std::string format = stream.ConsumeRemainingBytesAsString();

    // Call the target function
    avahi_string_list_add_printf(strList, const_cast<char *>(format.c_str()));

    // Free the string list
    avahi_string_list_free(strList);

    return 0;
}