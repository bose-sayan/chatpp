#include <boost/asio.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  // Boost.Asio example
  boost::asio::io_context io_context;
  std::cout << "Boost.Asio is set up correctly!" << std::endl;

  // nlohmann JSON example
  nlohmann::json json_example;
  json_example["message"] = "nlohmann JSON is set up correctly!";
  std::cout << json_example.dump(4) << std::endl;
  return 0;
}
