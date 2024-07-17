#include "client.hpp"
#include "helper.hpp"
#include "message.hpp"
#include "server.hpp"
#include <boost/asio.hpp>
#include <iostream>


int main(int argc, char *argv[]) {
    try {
        boost::asio::io_context io_context;
        Server server(io_context, "0.0.0.0", "12345");
        server.start();
        io_context.run();
    } catch (std::exception &e) {
        Logger::log(std::string("Exception: ") + e.what());
    }
    return 0;
}