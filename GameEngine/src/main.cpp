#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../image_loader/stb_image.h"

#include "ErrorHandler.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Shader.h"
#include "Camera.h"
#include "input.h"

#include "Snake/Snake.h"

#define WINDOW_TITLE "LearnOpenGL"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

void closeApp();

void clearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput();

GLFWwindow* createWindow(const char* title, int width, int height, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

unsigned int createTexture(std::string filePath, unsigned int format, unsigned int wrapping, unsigned int filter);

float lastX = 400, lastY = 300;

bool firstMouse = true;

Camera ourCam(glm::vec3(10.0f, 10.0f, 10.0f));

Snake* snake;
GLFWwindow* window;

int main() {

    window = createWindow(WINDOW_TITLE, SCR_WIDTH, SCR_HEIGHT);
    
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

    GE::Input::initializeInput(window);


    // ====== VAO =========

    // create vertex array object
    VertexArray VA;

    // ====== VBO ========

    // gernerate vertex buffer object
    VertexBuffer VB(cubeVertices, sizeof(cubeVertices));

    // link vertex attributes
    VertexBufferLayout vbl;

    vbl.push<float>(3);
    vbl.push<float>(2);

    VA.addBuffer(VB, vbl);

    VA.unbind();
    

    Shader cubeShader("shader/colorShader.vs", "shader/colorShader.fs");

    CubeObject cube(cubeShader, cubeVertices2, sizeof(cubeVertices2));
    snake = new Snake(20, cube);


    // ========================================
    // ============ Game Loop ===============
    // ========================================

    float passedTime = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        //=== input ===
        GE::Input::updateInput();
        processInput();

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


        cubeShader.use();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(ourCam.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        cubeShader.setMat4("projection", projection);



        // view matrix
        glm::mat4 view;
        view = ourCam.GetViewMatrix();
        cubeShader.setMat4("view", view);

        passedTime += deltaTime;
        float movesPerSecond = 10.0f;
        if (passedTime >= 1.0f/movesPerSecond) {
            passedTime -= 1.0f/movesPerSecond;
            if(!snake->move()) {
                glfwSetWindowShouldClose(window, true);
            }
        }

        snake->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteShader(ourShader.ID);
    glDeleteTextures(1,&texture1);
    glDeleteTextures(1,&texture2);

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

// process all input using the Input class
void processInput()
{
    if (GE::Input::Q.down())
        closeApp();

    if (GE::Input::E.down())
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    const float cameraSpeed = 2.8f * deltaTime; // adjust accordingly
    if (GE::Input::W.down())
        ourCam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);//cameraPos += cameraSpeed * cameraFront;
    if (GE::Input::S.down())
        ourCam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);//cameraPos -= cameraSpeed * cameraFront;
    if (GE::Input::A.down())
        ourCam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (GE::Input::D.down())
        ourCam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (GE::Input::SHIFT_L.down())
        ourCam.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);//cameraPos -= cameraUp * cameraSpeed;
    if (GE::Input::SPACE.down())
        ourCam.ProcessKeyboard(Camera_Movement::UP, deltaTime);//cameraPos += cameraUp * cameraSpeed;

    if (GE::Input::MOUSE.moving()) {
        ourCam.ProcessMouseMovement(GE::Input::MOUSE.movementX(), -GE::Input::MOUSE.movementY(), true);
    }


    if (GE::Input::UP.justPressed())
        snake->setDir(Direction::NORTH);
    if (GE::Input::DOWN.justPressed())
        snake->setDir(Direction::SOUTH);
    if (GE::Input::LEFT.justPressed())
        snake->setDir(Direction::WEST);
    if (GE::Input::RIGHT.justPressed())
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

void closeApp() {
    glfwSetWindowShouldClose(window, true);
}
