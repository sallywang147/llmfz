Undefined symbols for architecture x86_64:
  "boost::json::parse_options::parse_options()", referenced from:
      FuzzHelper::FuzzHelper() in fuzzer.o
  "boost::json::stream_parser::stream_parser(boost::json::storage_ptr, boost::json::parse_options)", referenced from:
      FuzzHelper::useDefault() in fuzzer.o
      FuzzHelper::useMonotonic() in fuzzer.o
      FuzzHelper::useLocalBuffer() in fuzzer.o
      FuzzHelper::useDynLess() in fuzzer.o
  "boost::json::stream_parser::reset(boost::json::resource*)", referenced from:
      FuzzHelper::useMonotonic() in fuzzer.o
      FuzzHelper::useDynLess() in fuzzer.o
  "boost::json::stream_parser::write(boost::json::string_view, boost::system::error_code&)", referenced from:
      FuzzHelper::run(boost::json::stream_parser&) in fuzzer.o
  "boost::json::stream_parser::finish(boost::system::error_code&)", referenced from:
      FuzzHelper::run(boost::json::stream_parser&) in fuzzer.o
  "boost::json::serialize(boost::json::value const&)", referenced from:
      FuzzHelper::run(boost::json::stream_parser&) in fuzzer.o
  "boost::json::value::size() const", referenced from:
      FuzzHelper::run(boost::json::stream_parser&) in fuzzer.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)