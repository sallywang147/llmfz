#include "fuzzer/FuzzedDataProvider.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libxslt/transform.h"
#include "libxslt/xsltutils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < 3) {
        return 0;
    }

    FuzzedDataProvider fuzz_data(data, size);

    // Initialize libxslt
    xmlInitParser();
    xsltInit();

    // Create a xsltStylesheetPtr
    xsltStylesheetPtr style = xsltNewStylesheet();
    if (style == nullptr) {
        xmlCleanupParser();
        return 0;
    }

    // Create a xmlDocPtr
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    if (doc == nullptr) {
        xsltFreeStylesheet(style);
        xmlCleanupParser();
        return 0;
    }

    // Create parameters array
    char* params[2];
    std::string param1 = fuzz_data.ConsumeRandomLengthString();
    params[0] = const_cast<char*>(param1.c_str());
    params[1] = nullptr;

    // Call the target function
    xmlDocPtr result = xsltProfileStylesheet(style, doc, params, stdout);

    // Cleanup
    if (result != nullptr) {
        xmlFreeDoc(result);
    }
    xmlFreeDoc(doc);
    xsltFreeStylesheet(style);
    xmlCleanupParser();

    return 0;
}