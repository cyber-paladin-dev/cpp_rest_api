# C++ REST API Service

A lightweight REST API service demonstrating HTTP server capabilities using C++17 and the `cpp-httplib` library.

## Features

- ✅ Lightweight HTTP server built with cpp-httplib
- ✅ RESTful API design with JSON responses
- ✅ CRUD operations for user management
- ✅ In-memory data storage
- ✅ Error handling and HTTP status codes
- ✅ Multi-threaded request handling

## Building

### Prerequisites

- C++17 compatible compiler (g++, clang++)
- Make
- curl (for testing)

### Build Steps

```bash
# Build the project
make

# Build and run directly
make run
```

## Running the Server

```bash
./bin/main
```

The server will start on `http://localhost:8080` and display available endpoints.

**Output:**
```
Starting C++ REST API server on http://localhost:8080
Available endpoints:
  GET  /              - Health check
  GET  /users         - Get all users
  POST /users         - Create new user
  GET  /users/<id>    - Get user by ID
  DELETE /users/<id>  - Delete user by ID

Press Ctrl+C to stop the server.
```

## API Endpoints

### 1. Health Check
```bash
curl http://localhost:8080/
```

**Response:**
```json
{
  "status": "OK",
  "message": "C++ REST API Service is running"
}
```

### 2. Get All Users
```bash
curl http://localhost:8080/users
```

**Response:**
```json
[
  {
    "id": 1,
    "name": "Alice Johnson",
    "email": "alice@example.com"
  },
  {
    "id": 2,
    "name": "Bob Smith",
    "email": "bob@example.com"
  }
]
```

### 3. Get User by ID
```bash
curl http://localhost:8080/users/1
```

**Response:**
```json
{
  "id": 1,
  "name": "Alice Johnson",
  "email": "alice@example.com"
}
```

**Error (404 Not Found):**
```json
{
  "error": "User not found"
}
```

### 4. Create New User
```bash
curl -X POST -H "Content-Type: application/json" \
  -d '{"name":"Dana Davis","email":"dana@example.com"}' \
  http://localhost:8080/users
```

**Response (201 Created):**
```json
{
  "id": 4,
  "name": "Dana Davis",
  "email": "dana@example.com"
}
```

### 5. Delete User by ID
```bash
curl -X DELETE http://localhost:8080/users/4
```

**Response (200 OK):**
```json
{
  "message": "User deleted successfully",
  "id": 4
}
```

**Error (404 Not Found):**
```json
{
  "error": "User not found"
}
```

## Project Structure

```
cpp_rest_api/
├── Makefile               # Build configuration
├── README.md              # This file
├── src/
│   ├── main.cpp           # Server initialization and route registration
│   ├── user.cpp           # User model and helper implementations
│   └── user_routes.cpp    # User endpoint handlers
├── include/
│   ├── user.h             # User struct and helper declarations
│   ├── user_routes.h      # Route registration interface
│   └── cpp-httplib/
│       └── httplib.h      # HTTP server library
├── bin/
│   └── main               # Compiled executable
└── lib/
```

## Architecture

The codebase is organized into separate modules for better maintainability:

- **src/main.cpp**: Server initialization, sample data setup, and route registration
- **src/user.cpp & include/user.h**: User model and business logic (storage, parsing, deletion helpers)
- **src/user_routes.cpp & include/user_routes.h**: Route handlers for all user endpoints
- **httplib::Server**: Handles HTTP requests and responses
- **In-memory storage**: Vector-based user database (can be replaced with persistent storage)

## Testing Examples

```bash
# Health check
curl http://localhost:8080/

# Get all users
curl http://localhost:8080/users

# Create a user
curl -X POST -H "Content-Type: application/json" \
  -d '{"name":"John Doe","email":"john@example.com"}' \
  http://localhost:8080/users

# Get specific user
curl http://localhost:8080/users/1

# Delete a user
curl -X DELETE http://localhost:8080/users/1

# Try to get deleted user (should return 404)
curl http://localhost:8080/users/1
```

## Implementation Details

### JSON Response Format

- All responses use `Content-Type: application/json`
- HTTP status codes follow REST conventions:
  - **200 OK**: Successful GET/DELETE
  - **201 Created**: Successful POST
  - **400 Bad Request**: Invalid request body
  - **404 Not Found**: Resource doesn't exist

### Future Enhancements

- Persistent storage (database integration)
- PUT endpoint for user updates
- Authentication and authorization
- Input validation
- Logging system
- Unit tests
- Docker containerization
