#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <boost/asio.hpp>

using namespace boost::asio;

class TcpServer {
public:
    TcpServer(io_service& io_service, const std::string& address, const std::string& port)
        : io_service_(io_service),
          acceptor_(io_service, ip::tcp::endpoint(ip::tcp::v4(), std::stoi(port))),
          socket_(io_service) {
        StartAccept();
    }

private:
    void StartAccept() {
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                std::cout << "New connection accepted" << std::endl;
            }

            StartAccept();
        });
    }

    io_service& io_service_;
    ip::tcp::acceptor acceptor_;
    ip::tcp::socket socket_;
};

void StartTcpServer(const std::string& address, const std::string& port) {
    io_service io_service;
    TcpServer server(io_service, address, port);
    io_service.run();
}

int main() {
    StartTcpServer("localhost", "8080");
    return 0;
}