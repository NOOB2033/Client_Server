#ifndef CLIENT_SERVER_BLOCKINGBUFFER_HPP
#define CLIENT_SERVER_BLOCKINGBUFFER_HPP


#include <vector>
#include <mutex>
#include <condition_variable>


template <typename T>
class BlockingBuffer {
public:

    BlockingBuffer() = default;
    ~BlockingBuffer() = default;

    void push(T value) {
        std::lock_guard lock(mutex);
        buffer.push_back(std::move(value));
        notEmpty.notify_one();
    }

    std::vector<T> take() {
        std::unique_lock lock(mutex);
        notEmpty.wait(lock, [&]() {
            return !buffer.empty() || closeBuffer;
        });
        std::vector<T> result = std::move(buffer);
        buffer.clear();
        return result;
    }

    bool empty() {
        std::lock_guard lock(mutex);
        return buffer.empty();
    }

    void close() {
        std::lock_guard lock(mutex);
        closeBuffer = true;
        notEmpty.notify_all();
    }

    bool isClosed() {
        std::lock_guard lock(mutex);
        return closeBuffer;
    }

private:

    bool closeBuffer{false};
    std::vector<T> buffer;
    std::mutex mutex;
    std::condition_variable notEmpty;
};


#endif //CLIENT_SERVER_BLOCKINGBUFFER_HPP
