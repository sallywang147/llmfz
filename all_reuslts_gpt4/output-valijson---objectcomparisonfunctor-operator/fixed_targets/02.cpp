#include <fuzzer/FuzzedDataProvider.h>
#include <valijson/adapters/adapter.hpp>
#include <valijson/adapters/generic_rapidjson_adapter.hpp>
#include <valijson/adapters/generic_rapidjson_array.hpp>
#include <valijson/adapters/generic_rapidjson_object.hpp>
#include <valijson/adapters/generic_rapidjson_value.hpp>
#include <valijson/adapters/basic_adapter.hpp>
#include <rapidjson/document.h>
#include <functional>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    rapidjson::Document document;
    std::string json = stream.ConsumeRemainingBytesAsString();
    document.Parse(json.c_str());

    valijson::adapters::GenericRapidJsonAdapter<> adapter(document);
    valijson::adapters::BasicAdapter<valijson::adapters::GenericRapidJsonAdapter<>, valijson::adapters::GenericRapidJsonArray<>, valijson::adapters::GenericRapidJsonObjectMember<>, valijson::adapters::GenericRapidJsonObject<>, valijson::adapters::GenericRapidJsonValue<>> basicAdapter(adapter);

    std::string str = stream.ConsumeRandomLengthString();
    std::function<void()> func = [](){};

    basicAdapter.ObjectComparisonFunctor::operator(&basicAdapter.ObjectComparisonFunctor, &str, func.target<void()>());

    return 0;
}