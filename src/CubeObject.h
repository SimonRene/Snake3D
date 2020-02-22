#pragma once


#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ErrorHandler.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Shader.h"


class CubeObject {
public:

    CubeObject(Shader& shader, const float* vertices, unsigned int verticesSize ,glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f))
    : m_VB(vertices, verticesSize), m_color(color), m_position(0.0f, 0.0f, 0.0f)
    {

        m_vertexCount = (verticesSize/4)/3;

        VertexBufferLayout vbl;
        vbl.push<float>(3);

        m_VA.addBuffer(m_VB, vbl);

        m_shader = &shader;
    } 

    void setColor(float r, float g, float b) {
        setColor(glm::vec3(r, g, b));
    }

    void setColor(glm::vec3 color) {
        m_color = color;
    }

    void setPosition(float x, float y, float z = 0.0f) {
        setPosition(glm::vec3(x, y, z));
    }

    void setPosition(glm::vec3 position) {
        m_position = position;
    }

    void draw()
    {
        GLcheck();
        m_shader->use();

        
        GLcheck();


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, m_position);

        m_shader->setMat4("model", model);




        GLcheck();
        m_shader->setVec3("ourColor", m_color.r, m_color.g, m_color.b);
        GLcheck();
        m_VA.bind();
        GLcheck();

        glDrawArrays(GL_TRIANGLES, 0, 36);
        GLcheck();
    }

private:
    VertexArray m_VA;
    VertexBuffer m_VB;

    glm::vec3 m_color;

    unsigned int m_vertexCount = 0;
    
    Shader* m_shader;

    glm::vec3 m_position;

};


#endif