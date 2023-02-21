#include "../include/ServerApplication.hpp"
#include "../include/Utils.hpp"


ServerApplication::ServerApplication()
    : server(context) {

}

ServerApplication::~ServerApplication() {
    stop();
}


void ServerApplication::start(const std::string& address, size_t port) {
    server.startAcception(address, port);

    boost::asio::streambuf buffer;
    while (true) {
        try {
            readingData(buffer);
        }
        catch (std::exception& ex) {
            std::cout << "Disconnecting connection" << std::endl;
            break;
        }

        std::string str;
        std::istream is(&buffer);
        std::getline(is, str);
        if (utils::dataChecking(str)) {
            std::cout << "Data received: " + str << std::endl;
        } else {
            std::cout << "Error: Data not validated" << std::endl;
        }
    }
}

void ServerApplication::stop() noexcept {
    server.stopConnection();
}


void ServerApplication::readingData(boost::asio::streambuf& buffer) {
    server.read(buffer);
}
