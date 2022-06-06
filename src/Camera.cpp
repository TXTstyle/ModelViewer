#include "Camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Math.hpp"

Camera::Camera(const vec2i &p_res, const vec2f p_clip, float p_fov, float p_camSpeed)
: camSpeed(p_camSpeed), camFov(p_fov), winRes(p_res) {
    projMat = glm::perspective(glm::radians(camFov), ((float)winRes.x/winRes.y), p_clip.x, p_clip.y);
    viewMat = glm::mat4(1.0f);
}

Camera::~Camera() {
    
}

float scroll = 1;
double mouseX, mouseY;

void Camera::Controls(Renderer &renderer) {

    if (firstMouse) // initially set to true
    {
        lastX = mouseX;
        lastY = mouseX;
        firstMouse = false;
    }

    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY; // reversed since y-coordinates range from bottom to top
    lastX = mouseX;
    lastY = mouseY;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;  

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camFront = glm::normalize(direction);

    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        exit(0);
    } 

    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float speed = deltaTime * camSpeed;
    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 3.0f;
    } else if(glfwGetKey(renderer.getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        speed *= 0.5f;
    } else { speed = deltaTime * camSpeed; }
    
    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        camPos += speed * camFront;
    }
    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        camPos -= speed * camFront;
    }
    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        camPos -= glm::normalize(glm::cross(camFront, camUp)) * speed;
    }
    if(glfwGetKey(renderer.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        camPos += glm::normalize(glm::cross(camFront, camUp)) * speed;
    }
    
    viewMat = glm::lookAt(camPos, camPos + camFront, camUp);
    //viewMat = glm::scale(viewMat, glm::vec3( scroll, scroll, 1.0f));
    scroll = 1;
    camDir = glm::vec2(0.0f);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0)
    {
        scroll = 1.05;
    }else if(yoffset < 0) {scroll = 0.95f; }
}

glm::mat4& Camera::getProjMat() {
    return projMat;
}

glm::mat4& Camera::getViewMat() {
    return viewMat;
}