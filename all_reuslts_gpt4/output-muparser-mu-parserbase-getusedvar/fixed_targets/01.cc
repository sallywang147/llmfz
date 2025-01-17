#include <fuzzer/FuzzedDataProvider.h>
#include <muParser.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string expr = stream.ConsumeRandomLengthString();
  
  try {
    mu::Parser parser;
    parser.SetExpr(expr);
    parser.Eval();
    std::map<std::string, double> *usedVars = parser.GetUsedVar();
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }

  return 0;
}