#include "../include/ServerApplication.hpp"


int main() {
    ServerApplication server;
    try {
        server.start("127.0.0.1", 1024);
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
