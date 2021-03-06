#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Math.hpp"
#include "Renderer.hpp"

class Camera
{
private:
    const vec2i &winRes;
    glm::vec2 camDir;

    float camSpeed;
    float camFov;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = winRes.x/2, lastY = winRes.y/2;
    bool firstMouse = true;
    float sensitivity = 0.075f;

    glm::vec3 camPos = glm::vec3(-5.0f, 0.0f, 0.0f);
    glm::vec3 camFront = glm::vec3(0.0f,  0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float deltaTime;
    float lastFrame;

    glm::mat4 projMat;
    glm::mat4 viewMat;
public:
    Camera(const vec2i &p_res, const vec2f p_clip, float p_fov, float p_camSpeed);
    ~Camera();

    glm::mat4& getProjMat();
    glm::mat4& getViewMat();

    void Controls(Renderer &renderer);
    //GLFWscrollfun scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
