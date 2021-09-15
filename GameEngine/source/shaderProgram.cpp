#include "../include/shaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>


namespace GE {



ShaderProgram::ShaderProgram(VertexShader* vertex, FragmentShader* fragment, GE::GeometryShader* geometry) {

    // link shaders
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex->id());
    glAttachShader(m_id, fragment->id());
    if(geometry != nullptr)
        glAttachShader(m_id, geometry->id());
    glLinkProgram(m_id);

    checkCompileErrors(m_id, "PROGRAM");
}


ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath, std::string geometryPath) {

    VertexShader* vertex = nullptr;
    FragmentShader* fragment = nullptr;
    GeometryShader* geometry = nullptr;

    vertex = new VertexShader(vertexPath);
    fragment = new FragmentShader(fragmentPath);
    if(geometryPath != "")
        geometry = new GeometryShader(geometryPath);

    // link shaders
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex->id());
    glAttachShader(m_id, fragment->id());
    if(geometry != nullptr)
        glAttachShader(m_id, geometry->id());
    glLinkProgram(m_id);

    checkCompileErrors(m_id, "PROGRAM");

    delete vertex;
    delete fragment;
    if(geometry != nullptr)
        delete geometry;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);
}

void ShaderProgram::use() {
    glUseProgram(m_id);
}

unsigned int ShaderProgram::id() {
    return m_id;
}




void ShaderProgram::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void ShaderProgram::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]); 
}
void ShaderProgram::setVec2(const std::string &name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]); 
}
void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]); 
}
void ShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}






// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void ShaderProgram::checkCompileErrors(GLuint shader, std::string type)
{
    (void)type;
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}


}