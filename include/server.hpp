#pragma once

#include <boost/asio.hpp>
#include <string>
#include<set>
#include <memory>
#include <mutex>

class Server : public std::enable_shared_from_this<Server> {

private:

    void accept_connection();

    void
    handle_accept(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, const boost::system::error_code &error);

    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::set<std::shared_ptr<boost::asio::ip::tcp::socket>> clients_;
    std::mutex clients_mutex_;
    std::string buffer_;

    void read_message(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket);

    void
    handle_read(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, const boost::system::error_code &error,
                std::size_t length);

    void send_pong(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket);

public:
    Server(boost::asio::io_context
           &io_context,
           const std::string &address,
           const std::string &port
    );

    void start();

};