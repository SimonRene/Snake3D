#include "VertexBufferLayout.h"


template<>
void VertexBufferLayout::push<float>(unsigned int count)
{
   m_elements.push_back({GL_FLOAT, count, GL_FALSE});

   // m_elements.emplace_back({GL_FLOAT, count, GL_FALSE});
   m_stride += (count * 4);
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
   m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
   m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
   m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_FALSE});
   m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}
