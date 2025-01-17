#include <fuzzer/FuzzedDataProvider.h>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <jsoncons_ext/jsonpath/json_query.hpp>
#include <jsoncons_ext/cbor/cbor.hpp>
#include <jsoncons_ext/cbor/cbor_encoder.hpp>
#include <jsoncons_ext/cbor/cbor_reader.hpp>
#include <jsoncons_ext/cbor/cbor_serializer.hpp>
#include <jsoncons_ext/cbor/cbor_view.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    jsoncons::json_decoder<jsoncons::json> decoder;
    std::error_code ec;
    std::exception ex;

    // We need to call visit_end_object, but it needs to be called in a valid context.
    // So, we first call visit_begin_object.
    if (!decoder.visit_begin_object(ec)) {
        return 0;
    }

    // Now we can call visit_end_object.
    decoder.visit_end_object(&ex, &ec);

    return 0;
}