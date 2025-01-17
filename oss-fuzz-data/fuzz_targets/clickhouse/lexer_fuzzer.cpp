#include <Parsers/Lexer.h>
#include <base/types.h>
#include <map>

#include <IO/ReadBufferFromMemory.h>
#include <IO/ReadHelpers.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  try {
    DB::String query;
    DB::ReadBufferFromMemory in(data, size);
    readStringUntilEOF(query, in);

    DB::Lexer lexer(query.data(), query.data() + query.size());

    while (true) {
      DB::Token token = lexer.nextToken();

      if (token.isEnd())
        break;

      if (token.isError())
        return 0;
    }
  } catch (...) {
  }

  return 0;
}
