#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "ErrorHandler.h"


struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        //ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
    
public:
    VertexBufferLayout() : m_stride(0) {}
    
    inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
    inline unsigned int getStride() const { return m_stride; }
    
    template<typename T>
    void push(unsigned int count);
    
    
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
    
};
/*
template<>
void VertexBufferLayout::push<float>(unsigned int count)
{
    m_elements.push_back({ GL_FLOAT, count, GL_FALSE });

    // m_elements.emplace_back({GL_FLOAT, count, GL_FALSE});
    m_stride += (count * 4);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
    m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

*/