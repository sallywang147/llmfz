#include <fuzzer/FuzzedDataProvider.h>
#include <muParser.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  mu::ParserBase parser;
  mu::ParserToken token1;
  mu::ParserToken token2;
  std::vector<mu::ParserToken> token_vec;

  // Consume data from the stream to initialize the tokens and vector
  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRandomLengthString();
  size_t vecSize = stream.ConsumeIntegralInRange<size_t>(0, 10);

  token1.SetVal(str1);
  token2.SetVal(str2);

  for (size_t i = 0; i < vecSize; i++) {
    mu::ParserToken token;
    std::string str = stream.ConsumeRandomLengthString();
    token.SetVal(str);
    token_vec.push_back(token);
  }

  try {
    parser.ApplyStrFunc(&token1, &parser, &token2, &token_vec);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }

  return 0;
}