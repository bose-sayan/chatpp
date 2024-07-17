#include "server.hpp"
#include "helper.hpp"
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

Server::Server(boost::asio::io_context &io_context, const std::string &address, const std::string &port) :
        io_context_(io_context),
        acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), stoi(port))) {}

void Server::start() {
    Logger::log("Server started");
    Logger::log("Listening on " + acceptor_.local_endpoint().address().to_string() + " :: " +
                std::to_string(acceptor_.local_endpoint().port()));
    accept_connection();
}

void Server::accept_connection() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code &error) {
        handle_accept(socket, error);
    });
}

void Server::handle_accept(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket,
                           const boost::system::error_code &error) {
    if (!error) {
        {
            std::lock_guard<std::mutex> lock(clients_mutex_);
            clients_.insert(socket);
        }
        Logger::log("Client connected: " + socket->remote_endpoint().address().to_string());
        // handle client communication
    } else {
        Logger::log("Accept error: " + error.message());
    }
    accept_connection();
}

void Server::read_message(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket) {
    auto self(shared_from_this());
    boost::asio::async_read_until(*socket, boost::asio::dynamic_buffer(buffer_), '\n',
                                  boost::bind(&Server::handle_read, this, socket, boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));
}

void
Server::handle_read(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, const boost::system::error_code &error,
                    std::size_t length) {
    if (!error) {
        std::string message(buffer_.substr(0, length));
        buffer_.erase(0, length);
        Logger::log("Message received: " + message);

        if (message == "PING\n") {
            send_pong(socket);
        }

        read_message(socket);
    } else {
        Logger::log("Read error: " + error.message());
        {
            std::lock_guard<std::mutex> lock(clients_mutex_);
            clients_.erase(socket);
        }
        socket->close();
    }
}

void Server::send_pong(const std::shared_ptr<boost::asio::ip::tcp::socket> &socket) {
    auto self(shared_from_this());
    std::string pong_message = "PONG\n";
    boost::asio::async_write(*socket, boost::asio::buffer(pong_message),
                             [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     Logger::log("PONG sent to client");
                                 } else {
                                     Logger::log("Send error: " + ec.message());
                                 }
                             });
}
