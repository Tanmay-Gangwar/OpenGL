#ifndef CAMERA_HPP
#define CAMERA_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

class Camera{
    bool firstClick = true;
    double lastXpos, lastYpos;
    public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camRight, camUp;
    glm::mat4 view = glm::mat4(1.0f);

    float speed = 0.1f;
    float sensitivity = 0.005f;

    Camera(glm::vec3 position){
        this->position = position;
        glm::mat4 view = glm::lookAt(position, position + camFront, globalUp);
        calculateDirections();
    }

    void calculateDirections(){
        camRight = glm::normalize(glm::cross(camFront, globalUp));
        camUp = glm::normalize(glm::cross(camRight, camFront));
    }

    void processInputs(GLFWwindow* window){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position += speed * camFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position -= speed * camFront;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position += speed * camRight;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position -= speed * camRight;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) position += speed * camUp;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) position -= speed * camUp;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (firstClick){
            lastXpos = xpos;
            lastYpos = ypos;
            firstClick = false;
        }
        double deltaX = xpos - lastXpos;
        double deltaY = ypos - lastYpos;
        camFront = glm::rotate(camFront, (float)deltaX * sensitivity, -camUp);
        calculateDirections();
        camFront = glm::rotate(camFront, (float)deltaY * sensitivity, -camRight);
        calculateDirections();
        view = glm::lookAt(position, position + camFront, globalUp);
        lastXpos = xpos;
        lastYpos = ypos;
    }
};

#endif 