#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Debug.hpp"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "Math.hpp"



void GLAPIENTRY errorOccurredGL(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam);

class Renderer
{
private:
    GLFWwindow* window;
    const vec2i &windowSize;
public:
    Renderer(const vec2i &windowSize, std::string windowName);
    ~Renderer();

    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear(const vec3f color);

    GLFWwindow* getWindow();
    bool WindowShouldClose();
    void EndEvents();
    void InitEnable();
};
