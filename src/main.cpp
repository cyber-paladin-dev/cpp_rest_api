#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cpp-httplib/httplib.h>
#include "../include/user.h"
#include "../include/user_routes.h"

// Note: User model, storage and helpers are defined in include/user.h and src/user.cpp

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

    // Register user-related routes
    register_user_routes(svr);
    
    // Start server
    std::cout << "Starting C++ REST API server on http://localhost:8080" << std::endl;
    std::cout << "Available endpoints:" << std::endl;
    std::cout << "  GET  /              - Health check" << std::endl;
    std::cout << "  GET  /users         - Get all users" << std::endl;
    std::cout << "  POST /users         - Create new user" << std::endl;
    std::cout << "  GET  /users/<id>    - Get user by ID" << std::endl;
    std::cout << "  DELETE /users/<id>  - Delete user by ID" << std::endl;
    std::cout << "\nPress Ctrl+C to stop the server." << std::endl;
    
    svr.listen("localhost", 8080);
    
    return 0;
}