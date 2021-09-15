
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class IndexBuffer {

public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    bool bind() const;
    bool unbind() const;

private:
    unsigned int m_RendererID = 0;

};
