#include "VertexArray.h"

#include "ErrorHandler.h"

void myPrint(std::string p) 
{
    std::cout << p << std::endl;
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_rendererID);
}


void VertexArray::addBuffer(const IndexBuffer& ib)
{
    bind();
    ib.bind();
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    
    for(int i = 0; i < elements.size(); ++i) {
        
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        unsigned int size = VertexBufferElement::GetSizeOfType(element.type);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<const void*>(offset));
        glEnableVertexAttribArray(i);
        //GLcheck();

        offset += size * element.count;
    }
}


void VertexArray::bind()
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
