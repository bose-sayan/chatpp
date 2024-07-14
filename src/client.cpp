#include "client.hpp"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

Client::Client(boost::asio::io_context &io_context, const std::string &host,
               const std::string &port)
    : socket_(io_context) {
  boost::asio::ip::tcp::resolver resolver(io_context);
  boost::asio::ip::tcp::resolver::results_type endpoints =
      resolver.resolve(host, port);
  boost::asio::connect(socket_, endpoints);
}

void Client::send_message(const Message &message) {
  auto json_message = message.to_json().dump() + "\n";
  boost::asio::write(socket_, boost::asio::buffer(json_message));
}

void Client::receive_message() {
  boost::asio::async_read_until(
      socket_, buffer_, "\n",
      boost::bind(&Client::handle_receive, this,
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void Client::handle_receive(const boost::system::error_code &error,
                            size_t bytes_transferred) {
  if (!error) {
    std::istream is(&buffer_);
    std::string line;
    std::getline(is, line);

    try {
      auto json_message = nlohmann::json::parse(line);
      Message message = Message::from_json(json_message);
      std::cout << "Received message: " << message.to_json().dump(4)
                << std::endl;
    } catch (const nlohmann::json::parse_error &e) {
      std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    receive_message();
  } else {
    std::cerr << "Error: " << error.message() << std::endl;
  }
}