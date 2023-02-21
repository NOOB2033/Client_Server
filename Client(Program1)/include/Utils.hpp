#ifndef CLIENT_SERVER_UTILS_HPP
#define CLIENT_SERVER_UTILS_HPP


#include <string>
#include <algorithm>


namespace utils {

bool clientDataChecking(std::string& data) {
    if (!std::all_of(data.begin(), data.end(), isdigit) || data.size() > 64) {
        return false;
    }
    std::sort(data.begin(), data.end(), std::less<>());
    std::string result;
    for (auto&& digit : data) {
        if ((digit - '0') % 2) {
            result += digit;
        } else {
            result += "KB";
        }
    }
    data = std::move(result);
    return true;
}

size_t clientDataSum(const std::string& data) {
    size_t sum = 0;
    for (auto&& value : data) {
        if (std::isdigit(value)) {
            sum += value - '0';
        }
    }
    return sum;
}

}


#endif //CLIENT_SERVER_UTILS_HPP
