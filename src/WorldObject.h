#pragma once


#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "ErrorHandler.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Shader.h"




class WorldObject {


public:
    WorldObject(const float* vertices, unsigned int verticesSize, unsigned int texture1, unsigned int texture2, Shader& shader)
    : m_VB(vertices, verticesSize)
    {
        //m_VB = VertexBuffer(vertices, verticesSize);

        m_vertexCount = (verticesSize/4) / 5;

        VertexBufferLayout vbl;
        vbl.push<float>(3);
        vbl.push<float>(2);

        m_VA.addBuffer(m_VB, vbl);

        m_shader = &shader;

        m_texture1 = texture1;
        m_texture2 = texture2;
    } 

    void draw()
    {
        m_shader->use();

        m_VA.bind();

        // // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texture2);

        glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    }

private:
    VertexArray m_VA;
    VertexBuffer m_VB;

    unsigned int m_texture1 = 0;
    unsigned int m_texture2 = 0;

    unsigned int m_vertexCount = 0;
    

    Shader* m_shader;


};