#include "../include/ClientApplication.hpp"
#include "../include/Utils.hpp"


ClientApplication::ClientApplication()
    : client(context) {

}


void ClientApplication::start(const std::string& address, size_t port, const std::string& stopMessage) {
    this->stopMessage = stopMessage;
    // main thread = second thread
    client.startConnection(address, port);

    std::thread producer([this]() { // this thread = first thread
        produceForBuffer();
    });

    consumeFromBuffer();

    producer.join();
}

void ClientApplication::stop() {
    stopWork.store(true);
    client.stopConnection();
}


void ClientApplication::produceForBuffer() {
    std::string message;
    while (!stopWork.load()) {
        std::getline(std::cin, message);

        if (message == stopMessage) {
            blockingBuffer.close();
            break;
        }

        if (!utils::clientDataChecking(message)) {
            std::cout << "Not correct data" << std::endl;
            continue;
        }

        blockingBuffer.push(std::move(message));
    }
}

void ClientApplication::consumeFromBuffer() {
    while (!stopWork.load()) {
        if (blockingBuffer.isClosed() && blockingBuffer.empty()) {
            std::cout << "The client has finished sending" << std:: endl;
            stop();
            break;
        }
        std::vector<std::string> messages = blockingBuffer.take();
        for (auto&& message : messages) {
            std::cout << message << std::endl;
            size_t result = utils::clientDataSum(message);
            try {
                client.write(std::to_string(result) + '\n');
            }
            catch (std::exception& ex) {
                std::cout << "Write error: " << ex.what() << std::endl;
                stop();
                break;
            }
        }
    }
}
