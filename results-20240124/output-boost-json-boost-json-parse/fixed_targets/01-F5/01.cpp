#include <boost/json/parse.hpp>

int main() {
  std::string json = R"({"name": "John Doe", "age": 30})";
  boost::json::value v = boost::json::parse(json);

  std::cout << v["name"].get<std::string>() << std::endl;
  std::cout << v["age"].get<int>() << std::endl;

  return 0;
}