#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"
#include "Camera.hpp"


void GLAPIENTRY errorOccurredGL(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam) {
  printf("Message from OpenGL:\nSource: 0x%x\nType: 0x%x\n"
         "Id: 0x%x\nSeverity: 0x%x\n", source, type, id, severity);
  printf("%s\n", message);
  //exit(-1);
}

Renderer::Renderer(const vec2i &p_windowSize, std::string p_windowName)
: windowSize(p_windowSize) {
    /* Initialize the library */
    if (!glfwInit())
        exit(-1);
    
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowSize.x, windowSize.y, p_windowName.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    std::cout << glGetString(GL_VERSION) << std::endl;


    if (glewInit() != GLEW_OK)
        throw std::runtime_error("GLEW not OK!");
}

Renderer::~Renderer() {
    glfwTerminate();
}

GLFWwindow* Renderer::getWindow() {
    return window;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(const vec3f color) {
    glClearColor(color.x, color.y, color.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Renderer::WindowShouldClose() {
    return (bool)glfwWindowShouldClose(window);
}

void Renderer::EndEvents() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::InitEnable() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(errorOccurredGL, NULL);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}