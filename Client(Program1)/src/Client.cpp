#include "../include/Client.hpp"


Client::Client(boost::asio::io_context& context)
    : context(context) {

}


void Client::startConnection(const std::string& address, size_t port) {
    if (isConnected()) {
        throw std::runtime_error("Connection already connected");
    }

    endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port);

    connect();
}

void Client::stopConnection() noexcept {
    socketPtr.reset();
}

bool Client::isConnected() const noexcept {
    return static_cast<bool>(socketPtr);
}

void Client::write(const std::string& data) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected");
    }
    boost::system::error_code errorCode;
    socketPtr->write_some(boost::asio::buffer(data.data(), data.size()), errorCode);
    if (errorCode) {
        stopConnection();
        connect();

        socketPtr->write_some(boost::asio::buffer(data.data(), data.size()));
    }
}


bool Client::tryConnect() {
    boost::system::error_code errorCode;
    socketPtr->connect(endpoint, errorCode);
    if (errorCode) {
        std::cout << "Connection error, trying to reconnect within 60 seconds" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d;
        while (errorCode) {
            d = std::chrono::high_resolution_clock::now() - start;
            socketPtr->connect(endpoint, errorCode);
            if (std::chrono::duration_cast<std::chrono::seconds>(d).count() > 60) {
                return false;
            }
        }
    }
    std::cout << "Connect successful" << std::endl;
    return true;
}

void Client::connect() {
    socketPtr = std::make_unique<boost::asio::ip::tcp::socket>(context);
    if (!tryConnect()) {
        socketPtr.reset();
        throw std::runtime_error("Connection error");
    }
}
