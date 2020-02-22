
#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __builtin_debugtrap()

#define GLcheck() ASSERT(ErrorHandler::GLLogCall(__FILE__, __LINE__))

class ErrorHandler {

public:

    static void GLClearErrors()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static bool GLLogCall(const char* file, int line)
    {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << ")" << " File: " << file << " Line: " << line << std::endl;
            return false;
        }

        return true;
    }


// Singleton
public:
    static ErrorHandler& get() {
        static ErrorHandler instance;
        return instance;
    }
private:
    ErrorHandler() = default;
    ErrorHandler(const ErrorHandler& t) = delete;
    ErrorHandler(const ErrorHandler&& t) = delete;
    ErrorHandler& operator=(ErrorHandler& t);
};
