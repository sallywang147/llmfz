extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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
  if (input.size() < kMinInputLength || input.size() > kMaxInputLength)
    return 0;

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

  // Extract type of scalar from 'flags' and check if the input string satisfies
  // the scalar type.
  const auto ref_res =
      ScalarReferenceResult::Check(flags & flags_scalar_type, input);
  auto &recheck = ref_res.matched;

  // Create parser
  flatbuffers::IDLOptions opts;
  opts.force_defaults = true;
  opts.output_default_scalars_in_json = true;
  opts.indent_step = -1;
  opts.strict_json = true;

  flatbuffers::Parser parser(opts);
  auto schema =
      "table X { Y: " + std::string(ref_res.type) + "; } root_type X;";
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

    if (recheck.res != orig_done) {
      // look for "does not fit" or "doesn't fit" or "out of range"
      auto not_fit =
          (true == recheck.res)
              ? ((orig_back.find("does not fit") != std::string::npos) ||
                 (orig_back.find("out of range") != std::string::npos))
              : false;

      if (false == not_fit) {
        TEST_OUTPUT_LINE("Stage 1 failed: Parser(%d) != Regex(%d)", orig_done,
                         recheck.res);
        TEST_EQ_STR(orig_back.c_str(),
                    input.substr(recheck.pos, recheck.len).c_str());
        TEST_EQ_FUNC(orig_done, recheck.res);
      }
    }

    // Try to make quoted string and test it.
    std::string qouted_input;
    if (true == recheck.quoted) {
      // we can't simply remove quotes, they may be nested "'12'".
      // Original string "\'12\'" converted to "'12'".
      // The string can be an invalid string by JSON rules, but after quotes
      // removed can transform to valid.
      assert(recheck.len >= 2);
    } else {
      const auto quote = (flags & flags_quotes_kind) ? '\"' : '\'';
      qouted_input = input;  // copy
      qouted_input.insert(recheck.pos + recheck.len, 1, quote);
      qouted_input.insert(recheck.pos, 1, quote);
    }

    // Test quoted version of the string
    if (!qouted_input.empty()) {
      auto fix_scalar = "{\"Y\" : " + qouted_input + "}";
      std::string fix_back;
      auto fix_done = Parse(parser, fix_scalar, &fix_back);

      if (orig_done != fix_done) {
        TEST_OUTPUT_LINE("Stage 2 failed: Parser(%d) != Regex(%d)", fix_done,
                         orig_done);
        TEST_EQ_STR(fix_back.c_str(), orig_back.c_str());
      }
      if (orig_done) { TEST_EQ_STR(fix_back.c_str(), orig_back.c_str()); }
      TEST_EQ_FUNC(fix_done, orig_done);
    }

    // Create new parser and test default value
    if (true == orig_done) {
      flatbuffers::Parser def_parser(opts);  // re-use options
      auto def_schema = "table X { Y: " + std::string(ref_res.type) + " = " +
                        input + "; } root_type X;" +
                        "{}";  // <- with empty json {}!

      auto def_done = def_parser.Parse(def_schema.c_str());
      if (false == def_done) {
        TEST_OUTPUT_LINE("Stage 3.1 failed with _error = %s",
                         def_parser.error_.c_str());
        FLATBUFFERS_ASSERT(false);
      }
      // Compare with print.
      std::string ref_string, def_string;
      FLATBUFFERS_ASSERT(!GenText(
          parser, parser.builder_.GetBufferPointer(), &ref_string));
      FLATBUFFERS_ASSERT(!GenText(
          def_parser, def_parser.builder_.GetBufferPointer(), &def_string));
      if (ref_string != def_string) {
        TEST_OUTPUT_LINE("Stage 3.2 failed: '%s' != '%s'", def_string.c_str(),
                         ref_string.c_str());
        FLATBUFFERS_ASSERT(false);
      }
    }

    // Restore locale.
    if (use_locale) { FLATBUFFERS_ASSERT(setlocale(LC_ALL, "C")); }
  }

  return 0;
}

extern "C" char *
flatbuffers::JsonPrinter::PrintVector(flatbuffers::JsonPrinter *self, char *start,
                                   flatbuffers::Type *type, int index, char *end) {
  if (type->element == flatbuffers::TYPE_VECTOR) {
    auto vt = reinterpret_cast<const flatbuffers::Vector<flatbuffers::Offset<void>> *>(
        self->current_vector_->data());
    start = Print("[", start, end);
    for (uoffset_t i = 0; i < vt->size(); i++) {
      if (i) start = Print(", ", start, end);
      start = self->Print(vt->Get(i), start, end);
    }
    start = Print("]", start, end);
  } else {
    start = self->Print(self->current_vector_->data(), start, end);
  }
  return start;
}

extern "C" char *
flatbuffers::JsonPrinter::PrintVector(flatbuffers::JsonPrinter *self, char *start,
                                   flatbuffers::Type *type, uint32_t index, char *end) {
  if (type->element == flatbuffers::TYPE_VECTOR) {
    auto vt = reinterpret_cast<const flatbuffers::Vector<flatbuffers::Offset<void>> *>(
        self->current_vector_->data());
    start = Print("[", start, end);
    for (uoffset_t i = 0; i < vt->size(); i++) {
      if (i) start = Print(", ", start, end);
      start = self->Print(vt->Get(i), start, end);
    }
    start = Print("]", start, end);
  } else {
    start = self->Print(self->current_vector_->data(), start, end);
  }
  return start;
}