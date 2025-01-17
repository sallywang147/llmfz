#include <fuzzer/FuzzedDataProvider.h>
#include <muParser.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mu::ParserBase parser;
  mu::ParserToken token1;
  mu::ParserToken token2;
  std::vector<mu::ParserToken> vec;

  try {
    token1.SetIdx(stream.ConsumeIntegral<int>());
    token2.SetIdx(stream.ConsumeIntegral<int>());

    parser.ApplyStrFunc(&token1, &parser, &token2, &vec);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }

  return 0;
}