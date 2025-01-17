 #include <stddef.h>
#include <stdint.h>

#include <string>

#include "flatbuffers/idl.h"
#include "test_init.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Reserve one byte for Parser flags and one byte for repetition counter.
  if (size < 3) return 0;
  const uint8_t flags = data[0];
  // normalize to ascii alphabet
  const int extra_rep_number =
      std::max(5, (data[1] > '0' ? (data[1] - '0') : 0));
  data += 2;
  size -= 2;  // bypass

  // Guarantee 0-termination.
  const std::string original(reinterpret_cast<const char *>(data), size);
  auto input = std::string(original.c_str());  // until '\0'
  if (input.size() < 1 || input.size() > 3000) return 0;

  // Break comments in json to avoid complexity with regex matcher.
  // The string " 12345 /* text */" will be accepted if insert it to string
  // expression: "table X { Y: " + " 12345 /* text */" + "; }.
  // But strings like this will complicate regex matcher.
  // We reject this by transform "/* text */ 12345" to "@* text */ 12345".
  BreakSequence(input, "//", '@');  // "//" -> "@/"
  BreakSequence(input, "/*", '@');  // "/*" -> "@*"
  // { "$schema: "text" } is exceptional case.
  // This key:value ignored by the parser. Numbers can not have $.
  BreakSequence(input, "$schema", '@');  // "$schema" -> "@schema"
  // Break all known scalar functions (todo: add them to regex?):
  for (auto f : { "deg", "rad", "sin", "cos", "tan", "asin", "acos", "atan" }) {
    BreakSequence(input, f, '_');  // ident -> ident
  }

  // Create parser
  flatbuffers::IDLOptions opts;
  opts.force_defaults = true;
  opts.output_default_scalars_in_json = true;
  opts.indent_step = -1;
  opts.strict_json = true;

  flatbuffers::Parser parser(opts);
  auto schema =
      "table X { Y: string; } root_type X;";
  TEST_EQ_FUNC(parser.Parse(schema.c_str()), true);

  // The fuzzer can adjust the number repetition if a side-effects have found.
  // Each test should pass at least two times to ensure that the parser doesn't
  // have any hidden-states or locale-depended effects.
  for (auto cnt = 0; cnt < (extra_rep_number + 2); cnt++) {
    // Each even run (0,2,4..) will test locale independed code.
    auto use_locale = !!OneTimeTestInit::test_locale() && (0 == (cnt % 2));
    // Set new locale.
    if (use_locale) {
      FLATBUFFERS_ASSERT(setlocale(LC_ALL, OneTimeTestInit::test_locale()));
    }

    // Parse original input as-is.
    auto orig_scalar = "{\"Y\" : " + input + "}";
    std::string orig_back;
    auto orig_done = Parse(parser, orig_scalar, &orig_back);

    if (orig_done) {
      // Compare with print.
      std::string ref_string;
      FLATBUFFERS_ASSERT(!GenText(
          parser, parser.builder_.GetBufferPointer(), &ref_string));
      FLATBUFFERS_ASSERT(GenTextFile(&parser, &orig_back, &ref_string));
    }

    // Restore locale.
    if (use_locale) { FLATBUFFERS_ASSERT(setlocale(LC_ALL, "C")); }
  }
  return 0;
}