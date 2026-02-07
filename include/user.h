#pragma once
#include <string>
#include <vector>

struct User {
    int id;
    std::string name;
    std::string email;

    std::string toJson() const {
        return "{\"id\":" + std::to_string(id) +
               ",\"name\":\"" + name +
               "\",\"email\":\"" + email + "\"}";
    }
};

extern std::vector<User> users;
extern int nextUserId;

User parseUserFromJson(const std::string& body);
bool deleteUserById(int userId);
