#ifndef CLIENT_SERVER_CLIENT_HPP
#define CLIENT_SERVER_CLIENT_HPP


#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <chrono>


class Client final {
public:

    Client(boost::asio::io_context& context);
    ~Client() = default;

    Client(const Client&) = delete;
    Client(Client&&) = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;


    void startConnection(const std::string& address, size_t port);
    void stopConnection() noexcept;
    bool isConnected() const noexcept;
    void write(const std::string& data);

private:

    bool tryConnect();
    void connect();

    boost::asio::io_context& context;
    boost::asio::ip::tcp::endpoint endpoint;
    std::unique_ptr<boost::asio::ip::tcp::socket> socketPtr;
};


#endif //CLIENT_SERVER_CLIENT_HPP
