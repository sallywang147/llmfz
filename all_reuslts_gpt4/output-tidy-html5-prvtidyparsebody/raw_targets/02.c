#include <fuzzer/FuzzedDataProvider.h>
#include "tidy.h"
#include "tidy-int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    TidyDoc tdoc = tidyCreate();                     // Initialize "document"
    FuzzedDataProvider stream(data, size);

    int mode = stream.ConsumeIntegral<int>();
    int rc = -1;
    Bool ok;

    // The input is going to be consumed as a c-string for libtidy.
    std::string s = stream.ConsumeRemainingBytesAsString();
    ok = tidyParseString(tdoc, s.c_str());  // Parse the input
    if ( ok >= 0 )
        rc = tidyCleanAndRepair(tdoc);       // Tidy it up!
    if ( rc >= 0 )
        rc = tidyRunDiagnostics(tdoc);       // Kvetch
    if ( rc > 1 )                            // If error, force output.
        rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
        rc = tidySaveStdout(tdoc);           // Pretty Print

    // Now to the actual target function
    struct _TidyDocImpl * doc = (struct _TidyDocImpl *)tdoc;
    struct _Node * body = doc->root;
    prvTidyParseBody(doc, body, mode);

    tidyRelease(tdoc);
    return 0;
}