#include "../include/user_routes.h"
#include "../include/user.h"
#include <string>

void register_user_routes(httplib::Server& svr) {
    // Get all users
    svr.Get("/users", [](const httplib::Request&, httplib::Response& res) {
        std::string json = "[";
        for (size_t i = 0; i < users.size(); ++i) {
            json += users[i].toJson();
            if (i < users.size() - 1) json += ",";
        }
        json += "]";
        res.set_content(json, "application/json");
        res.status = 200;
    });

    // Create new user
    svr.Post("/users", [](const httplib::Request& req, httplib::Response& res) {
        if (req.body.empty()) {
            res.set_content("{\"error\":\"Empty request body\"}", "application/json");
            res.status = 400;
            return;
        }

        if (req.body.find("\"name\":") == std::string::npos ||
            req.body.find("\"email\":") == std::string::npos) {
            res.set_content("{\"error\":\"Missing required fields: name, email\"}", "application/json");
            res.status = 400;
            return;
        }

        User newUser = parseUserFromJson(req.body);
        users.push_back(newUser);
        res.set_content(newUser.toJson(), "application/json");
        res.status = 201;
    });

    // Get user by ID
    svr.Get("/users/(\\d+)", [](const httplib::Request& req, httplib::Response& res) {
        int userId = std::stoi(req.matches[1]);
        for (const auto& user : users) {
            if (user.id == userId) {
                res.set_content(user.toJson(), "application/json");
                res.status = 200;
                return;
            }
        }
        res.set_content("{\"error\":\"User not found\"}", "application/json");
        res.status = 404;
    });

    // Delete user by ID
    svr.Delete("/users/(\\d+)", [](const httplib::Request& req, httplib::Response& res) {
        int userId = std::stoi(req.matches[1]);

        if (deleteUserById(userId)) {
            res.set_content("{\"message\":\"User deleted successfully\",\"id\":" + std::to_string(userId) + "}", "application/json");
            res.status = 200;
        } else {
            res.set_content("{\"error\":\"User not found\"}", "application/json");
            res.status = 404;
        }
    });
}
