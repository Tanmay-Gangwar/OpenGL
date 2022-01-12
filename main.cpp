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

const float Spring_location = 7.0f;
const int cubes_count = 50;

glm::vec3 initial_cube_position = glm::vec3(3.0f, 0.0f, 0.0f);
float initial_spring_length = 2.8f;
float m = 1.0f, c = 0.4f, k = 10.0f, delta_t = 0.01f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

float rand(float l, float r){
    return l + (r - l) * rand() / RAND_MAX;
}

int main(){
    srand(0);
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
    Camera camera(glm::vec3(0.0f, 0.0f, 15.0f));
    // Spring spring(glm::vec3(0.0f, Spring_location, 0.0f), initial_spring_length);
    // Cube cube(initial_cube_position);
    std::vector<Cube> cubes;
    for (int i = 0; i < cubes_count; i++){
        cubes.push_back(Cube(rand(1.5f, 5.0f), rand(0.1f, 0.5f), glm::vec3(3.0f * (i - cubes_count / 2), -5.0f, rand(0.0f, -50.0f)), 0.0f));
        // Cube(2.0f, 0.4f, glm::vec3(5.0f, -4.0f, 0.0f), 0.0f)
    };

    std::vector<Spring> springs;
    for (int i = 0; i < cubes.size(); i++) {
        springs.push_back(Spring(glm::vec3(cubes[i].position.x, Spring_location, cubes[i].position.z), fabs(Spring_location - cubes[i].position.y), rand(5.0f, 20.0f)));
    }

    Floor floor(glm::vec3(0.0f, Spring_location, 0.0f));

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
        for (Spring &spring: springs) spring.draw(view, projection);
        // spring.length = cube.position.x + 3.8f;
        for (Cube &cube: cubes) cube.Draw(view, projection);
        floor.Draw(view, projection);
        if (start_simulation) {
            // cube.Simulate(m, c, k, delta_t, glm::vec3(0.0f, 0.0f, 0.0f));
            for (int i = 0; i < cubes.size(); i++){
                cubes[i].Simulate(springs[i].k, delta_t);
                springs[i].length = fabs(Spring_location - cubes[i].position.y);
            }
            // for (Cube &cube: cubes) cube.Simulate(k, delta_t);
        }
        // for (int i = 0; i < cubes.size(); i++) springs[i].length = fabs(Spring_location - cubes[i].position.y);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return -1;
}

