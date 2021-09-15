#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"



class VertexArray {
    
public:
    VertexArray();
    
    void addBuffer(const IndexBuffer& vb);

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    
    void bind();
    void unbind();
    
private:
    unsigned int m_rendererID;
    
    
};
