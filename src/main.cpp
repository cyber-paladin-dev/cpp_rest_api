#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cpp-httplib/httplib.h>

// Simple User structure
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

// In-memory user storage
std::vector<User> users;
int nextUserId = 1;

// Helper function to parse JSON body (simple version)
User parseUserFromJson(const std::string& body) {
    User user;
    user.id = nextUserId++;
    
    // Simple JSON parsing
    size_t namePos = body.find("\"name\":\"");
    if (namePos != std::string::npos) {
        size_t start = namePos + 8;
        size_t end = body.find("\"", start);
        user.name = body.substr(start, end - start);
    }
    
    size_t emailPos = body.find("\"email\":\"");
    if (emailPos != std::string::npos) {
        size_t start = emailPos + 9;
        size_t end = body.find("\"", start);
        user.email = body.substr(start, end - start);
    }
    
    return user;
}

int main() {
    // Create HTTP server
    httplib::Server svr;
    
    // Initialize with some sample data
    users.push_back({1, "Alice Johnson", "alice@example.com"});
    users.push_back({2, "Bob Smith", "bob@example.com"});
    users.push_back({3, "Charlie Brown", "charlie@example.com"});
    nextUserId = 4;
    
    // Health check endpoint
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("{\"status\":\"OK\",\"message\":\"C++ REST API Service is running\"}", "application/json");
        res.status = 200;
    });
    
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
        if (!req.body.empty()) {
            User newUser = parseUserFromJson(req.body);
            users.push_back(newUser);
            res.set_content(newUser.toJson(), "application/json");
            res.status = 201;  // Created
        } else {
            res.set_content("{\"error\":\"Empty request body\"}", "application/json");
            res.status = 400;  // Bad Request
        }
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
        res.status = 404;  // Not Found
    });
    
    // Start server
    std::cout << "Starting C++ REST API server on http://localhost:8080" << std::endl;
    std::cout << "Available endpoints:" << std::endl;
    std::cout << "  GET  /              - Health check" << std::endl;
    std::cout << "  GET  /users         - Get all users" << std::endl;
    std::cout << "  POST /users         - Create new user" << std::endl;
    std::cout << "  GET  /users/<id>    - Get user by ID" << std::endl;
    std::cout << "\nPress Ctrl+C to stop the server." << std::endl;
    
    svr.listen("localhost", 8080);
    
    return 0;
}