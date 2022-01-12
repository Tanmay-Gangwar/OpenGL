#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<iostream>
#include"shader.hpp"
#include"buffer.hpp"

class Cube{
    public:
    glm::vec3 position, velocity, acceleration;
    glm::mat4 model;
    Shader shader;
    Buffer buffer;
    Texture texture;
    float size = 1.0f;
    float m, c;
    glm::vec3 mean_pos;
    Cube(float m, float c, glm::vec3 pos, float mean_pos){

        std::vector<float> vertices = {
            -size / 2.0f, -size / 2.0f, -size / 2.0f,      0.0f, 0.0f,
            -size / 2.0f, -size / 2.0f,  size / 2.0f,      0.0f, 1.0f,
            -size / 2.0f,  size / 2.0f, -size / 2.0f,      1.0f, 0.0f,
            -size / 2.0f,  size / 2.0f,  size / 2.0f,      1.0f, 1.0f,

             size / 2.0f, -size / 2.0f, -size / 2.0f,      0.0f, 0.0f,
             size / 2.0f, -size / 2.0f,  size / 2.0f,      0.0f, 1.0f,
             size / 2.0f,  size / 2.0f, -size / 2.0f,      1.0f, 0.0f,
             size / 2.0f,  size / 2.0f,  size / 2.0f,      1.0f, 1.0f,

            -size / 2.0f, -size / 2.0f, -size / 2.0f,      0.0f, 0.0f,
            -size / 2.0f, -size / 2.0f,  size / 2.0f,      0.0f, 1.0f,
             size / 2.0f, -size / 2.0f, -size / 2.0f,      1.0f, 0.0f,
             size / 2.0f, -size / 2.0f,  size / 2.0f,      1.0f, 1.0f,

            -size / 2.0f,  size / 2.0f, -size / 2.0f,      0.0f, 0.0f,
            -size / 2.0f,  size / 2.0f,  size / 2.0f,      0.0f, 1.0f,
             size / 2.0f,  size / 2.0f, -size / 2.0f,      1.0f, 0.0f,
             size / 2.0f,  size / 2.0f,  size / 2.0f,      1.0f, 1.0f,

            -size / 2.0f, -size / 2.0f, -size / 2.0f,      0.0f, 0.0f,
            -size / 2.0f,  size / 2.0f, -size / 2.0f,      0.0f, 1.0f,
             size / 2.0f, -size / 2.0f, -size / 2.0f,      1.0f, 0.0f,
             size / 2.0f,  size / 2.0f, -size / 2.0f,      1.0f, 1.0f,

            -size / 2.0f, -size / 2.0f,  size / 2.0f,      0.0f, 0.0f,
            -size / 2.0f,  size / 2.0f,  size / 2.0f,      0.0f, 1.0f,
             size / 2.0f, -size / 2.0f,  size / 2.0f,      1.0f, 0.0f,
             size / 2.0f,  size / 2.0f,  size / 2.0f,      1.0f, 1.0f,
        };

        std::vector<unsigned int> indices = {
             0,  1,  2,      1,  2,  3,
             4,  5,  6,      5,  6,  7,
             8,  9, 10,      9, 10, 11,
            12, 13, 14,     13, 14, 15,
            16, 17, 18,     17, 18, 19,
            20, 21, 22,     21, 22, 23
        };

        texture = Texture("container.png", GL_RGBA, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
        model = glm::mat4(1.0f);
        shader = Shader("cube.vert", "cube.frag");
        buffer = Buffer(vertices, indices, {3, 2});

        position = pos;
        velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        model = glm::translate(position);
        this->m = m;
        this->c = c;
        this->mean_pos = glm::vec3(position.x, mean_pos, position.z);
    }

    void Draw(glm::mat4 &view, glm::mat4 &projection){
        texture.Bind();
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        buffer.DrawTriangles();
    }

    void Simulate(float k, float delta_t){
        // ma + cv + kx = 0;
        glm::vec3 delta_v = acceleration * delta_t;
        glm::vec3 delta_x = velocity * delta_t;
        // std::cerr << "Position: " << position.x << " " << position.y << " " << position.z << "\n";
        // std::cerr << "velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << "\n";
        // std::cerr << "acceleration: " << acceleration.x << " " << acceleration.y << " " << acceleration.z << "\n";

        velocity += delta_v;
        position += delta_x;
        acceleration = - (k * (position - mean_pos) + c * velocity) / m;
        model = glm::translate(model, delta_x);
    }
};