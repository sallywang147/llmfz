#include <iostream>
#include <boost/json.hpp>

extern "C" {
#include <boost/json/parse.hpp>
}

int main() {
  std::string json_str = "{\"name\": \"John Doe\", \"age\": 30}";
  boost::json::value json_value;
  boost::json::parse_options options;
  options.allow_comments = true;
  boost::json::parse(&json_value, json_str.c_str(), json_str.length(), &options);

  std::cout << json_value << std::endl;
  return 0;
}