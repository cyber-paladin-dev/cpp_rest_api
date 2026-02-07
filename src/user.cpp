#include "../include/user.h"
#include <string>
#include <algorithm>

std::vector<User> users;
int nextUserId = 1;

User parseUserFromJson(const std::string& body) {
    User user;
    user.id = nextUserId++;

    size_t namePos = body.find("\"name\":\"");
    if (namePos != std::string::npos) {
        size_t start = namePos + 9;
        size_t end = body.find('"', start);
        if (end != std::string::npos) user.name = body.substr(start, end - start);
    }

    size_t emailPos = body.find("\"email\":\"");
    if (emailPos != std::string::npos) {
        size_t start = emailPos + 10;
        size_t end = body.find('"', start);
        if (end != std::string::npos) user.email = body.substr(start, end - start);
    }

    return user;
}

bool deleteUserById(int userId) {
    auto it = std::find_if(users.begin(), users.end(), [userId](const User& u){ return u.id == userId; });
    if (it != users.end()) {
        users.erase(it);
        return true;
    }
    return false;
}