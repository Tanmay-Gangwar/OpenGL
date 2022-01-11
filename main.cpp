#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<vector>
#include"buffer.hpp"
#include"shader.hpp"
#include"camera.hpp"
#include"texture.hpp"
#include"cube.hpp"
#include"spring.hpp"
#include"floor.hpp"

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

glm::vec3 initial_cube_position = glm::vec3(3.0f, 0.0f, 0.0f);
float initial_spring_length = 6.8f;
float m = 1.0f, c = 0.4f, k = 10.0f, delta_t = 0.01f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spring Mass model", NULL, NULL);

    if (window == NULL){
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize glad\n";
        return -1;
    }

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    Camera camera(glm::vec3(0.0f, 5.0f, 10.0f));
    camera.view = glm::lookAt(camera.position, glm::vec3(0.0f, 0.0f, 0.0f), camera.globalUp);
    Spring spring;
    spring.model = glm::translate(spring.model, glm::vec3(-4.0f, 0.0f, 0.0f));
    spring.length = initial_spring_length;
    Cube cube(initial_cube_position);
    Floor floor(glm::vec3(0.0f, 0.0f, 10.0f));

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool start_simulation = false;
        

    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) start_simulation = true;

        view = camera.view;
        camera.processInputs(window);
        spring.draw(view, projection);
        spring.length = cube.position.x + 3.8f;
        cube.Draw(view, projection);
        floor.Draw(view, projection);
        if (start_simulation) cube.Simulate(m, c, k, delta_t);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return -1;
}

