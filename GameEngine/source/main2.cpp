#define CHUNK_MANAGER

//#include <glad/glad.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

#include "../include/window.h"

#include "../include/input.h"

#include "../include/shaderProgram.h"

#include "../include/vao.h"
#include "../include/vbo.h"
#include "../include/ebo.h"

#include "../include/camera.h"
#include "../include/time.h"

#include "../include/mesh.h"

#include "../chunk.h"
#include "../ChunkManager.h"

#include "../texture.h"



using namespace GE;

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

void handeleInput(Window &window, Camera &camera);


int main2()
{
    Window window;

    window.initializeWindow(SCR_WIDTH, SCR_HEIGHT);

    ShaderProgram* shaderProgram = nullptr;
    
    shaderProgram = new ShaderProgram(".\\resource\\shaders\\vertex1.vertex", ".\\resource\\shaders\\fragment1.frag");
    
    Renderer* renderer = new Renderer(shaderProgram);

#ifndef CHUNK_MANAGER
    Chunk chunk(0,0,0);

    chunk.setRenderer(renderer);

    chunk.createMesh();
#endif

    GE::Camera camera(glm::vec3(6.0f, 50.0f, -12.0f));


    camera.setYaw(75.0f);

#ifdef CHUNK_MANAGER
    ChunkManager chunkManager(camera.Position());

    chunkManager.setRenderer(renderer);
#endif
   
    std::string texturePath = ".\\resource\\textures\\minecraft_v5.png";
    //std::string texturePath = ".\\resource\\textures\\ATLAS_v3.png";

    Texture texture(texturePath);


    shaderProgram->use();
    //glUniform1i(glGetUniformLocation(shaderProgram->id(), "texture1"), 0);
    shaderProgram->setInt("texture1", 0);


    //////////////////
    /*

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    int meshID = 0;
    renderer->createMesh(&meshID);

    glm::vec3 norm(0.0, 0.0, -1.0);


    unsigned int v0 = renderer->addVertexToMesh(meshID, glm::vec3(vertices[0], vertices[1], vertices[2]), norm, glm::vec2(vertices[6], vertices[7]));
    unsigned int v1 = renderer->addVertexToMesh(meshID, glm::vec3(vertices[8], vertices[9], vertices[10]), norm, glm::vec2(vertices[14], vertices[15]));
    unsigned int v2 = renderer->addVertexToMesh(meshID, glm::vec3(vertices[16], vertices[17], vertices[18]), norm, glm::vec2(vertices[22], vertices[23]));
    unsigned int v3 = renderer->addVertexToMesh(meshID, glm::vec3(vertices[24], vertices[25], vertices[26]), norm, glm::vec2(vertices[30], vertices[31]));


    renderer->addTriangleToMesh(meshID, v0, v1, v3);
    renderer->addTriangleToMesh(meshID, v1, v2, v3);

    renderer->finishMesh(meshID, 1, 1);
    */




    ////////////////////




    while (!window.shouldClose())
    {
        handeleInput(window, camera);



        window.clearWindow();

        window.updateTime();



        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id());

        shaderProgram->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians<float>((float)camera.Zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 projection = camera.getProjectionMatrix((float)SCR_WIDTH, (float)SCR_HEIGHT);
        shaderProgram->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shaderProgram->setMat4("view", view);

#ifndef CHUNK_MANAGER
        chunk.render();
#else
        chunkManager.update(camera.Position(), glm::vec3(0, 0, 1));
#endif
        //renderer->renderMesh(meshID);

        window.updateWindow();
    }

    //delete shaderProgram;

    delete renderer;

    window.destroyWindow();


    return 0;
}


void handeleInput(Window &window, Camera &camera) {
    Input::updateInput();

    // close app when ESCAPE was pressed
    if (Input::ESCAPE.justReleased())
        window.close();


    if (Input::SHIFT_L.justPressed()) {
        camera.setMovementSpeed(12.0f);
    }
    if (Input::SHIFT_L.justReleased()) {
        camera.setMovementSpeed(5.0f);
    }


    if (Input::MOUSE.moving()) {
        camera.ProcessMouseMovement((float)Input::MOUSE.movementX(), (float)Input::MOUSE.movementY());
    }

    if (Input::MOUSE.scrolling()) {
        camera.ProcessMouseScroll((float)Input::MOUSE.scrollY());
    }

    if (Input::W.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::FORWARD, (float)Time::deltaTime());
    }
    if (Input::A.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::LEFT, (float)Time::deltaTime());
    }
    if (Input::S.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::BACKWARD, (float)Time::deltaTime());
    }
    if (Input::D.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::RIGHT, (float)Time::deltaTime());
    }
    if (Input::SPACE.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::UP, (float)Time::deltaTime());
    }
    if (Input::CTRL_L.down()) {
        camera.ProcessKeyboard(GE::Camera_Movement::DOWN, (float)Time::deltaTime());
    }
}

