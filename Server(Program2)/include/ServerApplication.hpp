#ifndef CLIENT_SERVER_SERVERAPPLICATION_HPP
#define CLIENT_SERVER_SERVERAPPLICATION_HPP


#include "Server.hpp"


class ServerApplication final {
public:

    ServerApplication();
    ~ServerApplication();

    ServerApplication(const ServerApplication&) = delete;
    ServerApplication(ServerApplication&&) = delete;
    ServerApplication& operator=(const ServerApplication&) = delete;
    ServerApplication& operator=(ServerApplication&&) = delete;


    void start(const std::string& address, size_t port);
    void stop() noexcept;

private:

    void readingData(boost::asio::streambuf& buffer);

    boost::asio::io_context context;
    Server server;
};


#endif //CLIENT_SERVER_SERVERAPPLICATION_HPP
