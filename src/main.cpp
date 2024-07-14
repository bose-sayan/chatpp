#include "client.hpp"
#include "helper.hpp"
#include "message.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      Logger::log("Usage: chat <client|server>");
      return 1;
    }
    std::string mode = argv[1];
    boost::asio::io_context io_context;
    if (mode == "client") {
      Client client(io_context, "localhost", "8080");
      std::thread t([&io_context]() { io_context.run(); });
      while (true) {
        std::string text;
        std::getline(std::cin, text);
        Message message("Client", text, get_current_time());
        client.send_message(message);
      }
      t.join();
    } else {
      Logger::log("Invalid mode. Use client.");
      return 1;
    }
  } catch (const std::exception &e) {
    Logger::log(e.what());
    return 1;
  }
  return 0;
}