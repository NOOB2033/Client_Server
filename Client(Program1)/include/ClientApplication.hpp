#ifndef CLIENT_SERVER_CLIENTAPPLICATION_HPP
#define CLIENT_SERVER_CLIENTAPPLICATION_HPP


#include "Client.hpp"
#include "BlockingBuffer.hpp"
#include <thread>


class ClientApplication final {
public:

    ClientApplication();
    ~ClientApplication() = default;

    ClientApplication(const ClientApplication&) = delete;
    ClientApplication(ClientApplication&) = delete;
    ClientApplication& operator=(const ClientApplication&) = delete;
    ClientApplication& operator=(ClientApplication&&) = delete;


    void start(const std::string& address, size_t port, const std::string& stopMessage);
    void stop();

private:

    void produceForBuffer();
    void consumeFromBuffer();

    std::atomic<bool> stopWork{false};
    std::string stopMessage;
    BlockingBuffer<std::string> blockingBuffer;
    boost::asio::io_context context;
    Client client;
};


#endif //CLIENT_SERVER_CLIENTAPPLICATION_HPP
