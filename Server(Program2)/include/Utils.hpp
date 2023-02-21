#ifndef CLIENT_SERVER_UTILS_HPP
#define CLIENT_SERVER_UTILS_HPP


#include <string>


namespace utils {

bool dataChecking(const std::string& str) {
    //std::atoi because the client always sends a number
    return (str.size() >= 2) && (std::atoi(str.data()) % 32 == 0);
}

}


#endif //CLIENT_SERVER_UTILS_HPP
