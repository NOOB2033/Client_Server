#ifndef CLIENT_SERVER_SERVER_HPP
#define CLIENT_SERVER_SERVER_HPP


#include <boost/asio.hpp>
#include <iostream>


class Server final {
public:

    Server(boost::asio::io_context& context);
    ~Server() = default;

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    void startAcception(const std::string& address, size_t port);
    void stopConnection() noexcept;
    bool isConnected() const noexcept;
    void read(boost::asio::streambuf& buffer);

private:

    void accept();

    boost::asio::io_context& context;
    boost::asio::ip::tcp::endpoint endpoint;
    std::unique_ptr<boost::asio::ip::tcp::socket> socketPtr;
};


#endif //CLIENT_SERVER_SERVER_HPP
