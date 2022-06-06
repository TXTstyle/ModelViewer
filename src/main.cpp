#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <algorithm>
#include <memory>

#include "Math.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

const uint32_t MaxGrid = 1;
const uint32_t MaxQuads = MaxGrid*8;
const uint32_t MaxIndices = MaxQuads*36;

int main(void) {
    vec2i WinRes(1280, 720);

    Renderer renderer(WinRes, "Model Viewer");
    renderer.InitEnable();

    
    float pos[] = {
        -0.5f,-0.5f,-0.5f,    0.0f, 0.0f,   -0.5f,-0.5f,-0.5f, 
         0.5f,-0.5f,-0.5f,    1.0f, 0.0f,   -0.5f,-0.5f,-0.5f, 
         0.5f,-0.5f, 0.5f,    1.0f, 1.0f,   -0.5f,-0.5f,-0.5f, 
        -0.5f,-0.5f, 0.5f,    1.0f, 0.0f,   -0.5f,-0.5f,-0.5f, 
        
        -0.5f, 0.5f,-0.5f,    0.0f, 1.0f,   -0.5f,-0.5f,-0.5f, 
         0.5f, 0.5f,-0.5f,    1.0f, 1.0f,   -0.5f,-0.5f,-0.5f, 
         0.5f, 0.5f, 0.5f,    0.0f, 1.0f,   -0.5f,-0.5f,-0.5f, 
        -0.5f, 0.5f, 0.5f,    1.0f, 1.0f,   -0.5f,-0.5f,-0.5f 
    };

    
    uint32_t indices[] = { // 36 / 8v / 6s / 2t / 3600
        0, 3, 2,
        0, 2, 1,
        0, 1, 5,
        5, 4, 0,
        6, 1, 2,
        6, 5, 1,
        2, 7, 6,
        2, 3, 7,
        0, 4, 3,
        3, 4, 7,
        6, 7, 4,
        6, 4, 5,
        
    };


    VertexArray va;
    VertexBuffer vb(pos, sizeof(pos));
    VertexBufferLayout layout;
    layout.Push<float>(3, GL_FALSE);
    layout.Push<float>(2, GL_FALSE);
    layout.Push<float>(3, GL_FALSE);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(uint32_t));

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    Texture texture("res/textures/UV_grid.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Camera camera(WinRes, vec2f(0.1f, 500.0f), 45.0f, 3.0f);
    glfwSetScrollCallback(renderer.getWindow(), scrollCallback);
    glfwSetCursorPosCallback(renderer.getWindow(), mouseCallback);

    while (!renderer.WindowShouldClose())
    {
        renderer.Clear(vec3f(1.0f, 1.0f, 0.94f));

        vb.Bind();
        glm::mat4 mvp = camera.getProjMat() * camera.getViewMat() * glm::mat4(1.0f);
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);

        camera.Controls(renderer);

        renderer.EndEvents();
    }
    
    renderer.~Renderer();
    return 0;
}
