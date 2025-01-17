#include <fuzzer/FuzzedDataProvider.h>
#include "readstat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume data for value and variable
    size_t value = stream.ConsumeIntegral<size_t>();
    size_t variable = stream.ConsumeIntegral<size_t>();

    // Consume data for readstat_variable_s
    readstat_variable_t var;
    var.type = static_cast<readstat_type_t>(stream.ConsumeIntegral<int>());
    var.index = stream.ConsumeIntegral<int>();
    var.storage_width = stream.ConsumeIntegral<int>();
    var.display_width = stream.ConsumeIntegral<int>();
    var.measure = static_cast<readstat_measure_t>(stream.ConsumeIntegral<int>());
    var.alignment = static_cast<readstat_alignment_t>(stream.ConsumeIntegral<int>());
    var.endianness = static_cast<readstat_endianness_t>(stream.ConsumeIntegral<int>());

    // Call the target function
    int result = readstat_value_is_defined_missing(value, variable, &var);

    return 0;
}