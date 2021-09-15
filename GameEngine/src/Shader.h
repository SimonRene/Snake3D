//
//  Shader.h
//  LearnOpenGL
//
//  Created by Simon Stempfle on 2/18/20.
//  Copyright © 2020 Simon Stempfle. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // constructor reads and builds the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setVec3(const std::string &name, float x,  float y,  float z) const;
    void setVec4(const std::string &name, float x,  float y,  float z,  float w) const;

    void setMat4(const std::string &name, glm::mat4 mat);

private:
    unsigned int createVertexShader(const char* shaderSource);
    unsigned int createFragmentShader(const char* shaderSource);
    unsigned int createShaderProgram(unsigned int vertex, unsigned int fragment);
};


#endif /* Shader_h */
