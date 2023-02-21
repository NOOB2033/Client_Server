#include "../include/Server.hpp"


Server::Server(boost::asio::io_context& context)
    : context(context) {

}


void Server::startAcception(const std::string& address, size_t port) {
    endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port);

    accept();
}

void Server::stopConnection() noexcept {
    socketPtr.reset();
}

bool Server::isConnected() const noexcept {
    return static_cast<bool>(socketPtr);
}

void Server::read(boost::asio::streambuf& buffer) {

    if (!isConnected()) {
        throw std::runtime_error("Тo accepted connections");
    }

    try {
        boost::asio::read_until(*socketPtr, buffer, '\n');
    }
    catch (boost::system::system_error& error) {
        std::cout << "Read error. Connection reset. Reconnect." << std::endl;
        stopConnection();
        accept();

        boost::asio::read_until(*socketPtr, buffer, '\n');
    }
}


void Server::accept() {
    socketPtr = std::make_unique<boost::asio::ip::tcp::socket>(context);

    boost::asio::ip::tcp::acceptor acceptor(context, endpoint);
    acceptor.accept(*socketPtr);
    std::cout << "Connection accepted" << std::endl;
}
