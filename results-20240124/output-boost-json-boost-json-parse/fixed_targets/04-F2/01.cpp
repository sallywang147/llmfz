#include <boost/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

extern "C" {
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
}

int main() {
  std::string json_string = R"({
    "name": "John Doe",
    "age": 30,
    "city": "New York"
  })";

  // Create a gzip-compressed output stream
  std::ofstream compressed_file("data.json.gz", std::ios::binary);
  boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
  out.push(boost::iostreams::gzip_compressor());
  out.push(compressed_file);

  // Write the JSON string to the compressed stream
  boost::json::stream_parser parser(out);
  boost::system::error_code ec;
  parser.write(boost::string_view(json_string), ec);
  if (ec) {
    std::cerr << "Error writing JSON string: " << ec.message() << std::endl;
    return 1;
  }

  // Close the compressed stream
  out.close();

  return 0;
}