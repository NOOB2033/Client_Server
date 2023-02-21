#include "../include/ClientApplication.hpp"


int main() {
    ClientApplication client;
    try {
        client.start("127.0.0.1", 1024, "Stop!!!");
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
