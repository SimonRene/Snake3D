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
#include "Camera.h"

#include "Snake/Snake.h"

#define WINDOW_TITLE "LearnOpenGL"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGHT 600

float vertices[] = {
    // position          // color           // texture
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left
};

float vertices2[] = {
    // position          // color           // texture
     0.8f,  0.8f, 0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f, // top right
     0.8f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, // bottom right
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, // bottom left
     0.5f,  0.8f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, // top left
        
};

float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float cubeVertices2[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f,  0.0f,  0.0f), 
  glm::vec3( 2.0f,  5.0f, -15.0f), 
  glm::vec3(-1.5f, -2.2f, -2.5f),  
  glm::vec3(-3.8f, -2.0f, -12.3f),  
  glm::vec3( 2.4f, -0.4f, -3.5f),  
  glm::vec3(-1.7f,  3.0f, -7.5f),  
  glm::vec3( 1.3f, -2.0f, -2.5f),  
  glm::vec3( 1.5f,  2.0f, -2.5f), 
  glm::vec3( 1.5f,  0.2f, -1.5f), 
  glm::vec3(-1.3f,  1.0f, -1.5f)  
};

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

// Test

void clearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

GLFWwindow* createWindow(const char* title, int width, int height, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

unsigned int createTexture(std::string filePath, unsigned int format, unsigned int wrapping, unsigned int filter);

float lastX = 400, lastY = 300;

bool firstMouse = true;

Camera ourCam(glm::vec3(0.0f, 0.0f, 3.0f));

Snake* snake;

int main() {

    GLFWwindow* window = createWindow(WINDOW_TITLE, SCR_WIDTH, SCR_HEIGHT);
    
    if (!window) {
        std::cout << "An error occured." << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); 

    stbi_set_flip_vertically_on_load(true);


    // ========================================
    // ======== OpenGL Initialization =========
    // ========================================
    

    // ===== Shader program ======

    // create shader program
    Shader ourShader("shader/textureShader.vs", "shader/textureShader.fs");

    // load textures
    unsigned int texture1 = createTexture("images/container.jpg", GL_RGB, GL_REPEAT, GL_LINEAR);
    unsigned int texture2 = createTexture("images/awesomeface.png", GL_RGBA, GL_REPEAT, GL_LINEAR);

    ourShader.use(); // use our shader program
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);




    // ====== VAO =========

    // create vertex array object
    VertexArray VA;
    // VA.bind();


    // ====== VBO ========

    // gernerate vertex buffer object
    VertexBuffer VB(cubeVertices, sizeof(cubeVertices));
    //  VB.bind();
    GLcheck();

    // link vertex attributes
    VertexBufferLayout vbl;

    vbl.push<float>(3);
    //vbl.push<float>(3);
    vbl.push<float>(2);

    VA.addBuffer(VB, vbl);

    VA.unbind();
    
    GLcheck();

    // ====== EBO =======

    // create Element Buffer Object
    // IndexBuffer EB(indices, 6);

    // VA.addBuffer(EB);

    Shader cubeShader("shader/colorShader.vs", "shader/colorShader.fs");

    CubeObject cube(cubeShader ,cubeVertices2, sizeof(cubeVertices2));
    snake = new Snake(60, cube);

    GLcheck();


    //==============

    // ========================================
    // ============ Render Loop ===============
    // ========================================

    float passedTime = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  
        //=== input ===
        processInput(window);

        //=== render ===
        // clear screen
        clearScreen(0.2f, 0.3f, 0.3f);

        // draw triangle
        ourShader.use(); // use our shader program

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // GLcheck();
        GLcheck();
        
        /*
        // projection matrix
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(ourCam.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        GLcheck();

        // view matrix
        glm::mat4 view;
        view = ourCam.GetViewMatrix();
        ourShader.setMat4("view", view);

        GLcheck();

        VA.bind(); // bind the VAO that contains the object to be drawn

        float time = glfwGetTime();

        */

        // for(unsigned int i = 0; i < 10; i++)
        // {
        //     // model matrix
        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, cubePositions[i]);
        //     float angle = 20.0f * (i+1); 
        //     model = glm::rotate(model, time * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        //     ourShader.setMat4("model", model);

        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }
        cubeShader.use();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(ourCam.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        cubeShader.setMat4("projection", projection);

        GLcheck();

        // view matrix
        glm::mat4 view;
        view = ourCam.GetViewMatrix();
        cubeShader.setMat4("view", view);
        GLcheck();

        passedTime += deltaTime;
        float movesPerSecond = 40.0f;
        if (passedTime >= 1.0f/movesPerSecond) {
            passedTime -= 1.0f/movesPerSecond;
            if(!snake->move()) {
                glfwSetWindowShouldClose(window, true);
            }
        }

        GLcheck();
        snake->draw();

        GLcheck();


        //=== glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.) ===
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    //glDeleteVertexArrays(1, &VAO);

    glDeleteShader(ourShader.ID);
    glDeleteTextures(1,&texture1);
    glDeleteTextures(1,&texture2);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
  
    return 0;
}

void clearScreen(float r, float g, float b, float a)
{
    // clear screen
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    const float cameraSpeed = 2.8f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);//cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);//cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);//cameraPos -= cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        ourCam.ProcessKeyboard(Camera_Movement::UP, deltaTime);//cameraPos += cameraUp * cameraSpeed;


    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        snake->setDir(Direction::NORTH);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        snake->setDir(Direction::SOUTH);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        snake->setDir(Direction::WEST);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        snake->setDir(Direction::EAST);
    

}

GLFWwindow* createWindow(const char* title, int width, int height, GLFWmonitor* monitor, GLFWwindow* share)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetScrollCallback(window, scroll_callback); 

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    
    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

unsigned int createTexture(std::string filePath, unsigned int format, unsigned int wrapping, unsigned int filter)
{
    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    data = nullptr;

    return texture;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    ourCam.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ourCam.ProcessMouseScroll(yoffset);
}