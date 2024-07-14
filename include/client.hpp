#pragma once

#include "message.hpp"
#include <boost/asio.hpp>
#include <string>

class Client {
private:
  boost::asio::ip::tcp::socket socket_;
  boost::asio::streambuf buffer_;
  void handle_receive(const boost::system::error_code &error,
                      size_t bytes_transferred);

public:
  Client(boost::asio::io_context &io_context, const std::string &host,
         const std::string &port);
  void send_message(const Message &message);
  void receive_message();
};