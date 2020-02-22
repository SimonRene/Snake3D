
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    bool bind() const;
    bool unbind() const;

private:
    unsigned int m_RendererID = 0;

};
