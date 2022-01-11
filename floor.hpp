#ifndef FLOOR_HPP
#define FLOOR_HPP

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
#include"texture.hpp"

class Floor{
    public:
    glm::vec3 position;
    glm::mat4 model = glm::mat4(1.0f);
    Shader shader;
    Buffer buffer;
    Texture texture;
    Floor(glm::vec3 position){
        std::vector<float> vertices = {
            -200.0f, -0.499f,    0.0f,      0.0f,   0.0f,
             200.0f, -0.499f,    0.0f,      200.0f, 0.0f,
            -200.0f, -0.499f, -200.0f,    0.0f,   200.0f,
             200.0f, -0.499f, -200.0f,    200.0f, 200.0f
        };
        std::vector<unsigned int> indices = {
            0, 1, 2,
            1, 2, 3
        };
        texture = Texture("floor.png", GL_RGBA, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
        shader = Shader("floor.vert", "floor.frag");
        buffer = Buffer(vertices, indices, {3, 2});
        this->position = position;
        model = glm::translate(model, position);
    }

    void Draw(glm::mat4 &view, glm::mat4 &projection){
        texture.Bind();
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        buffer.DrawTriangles();
    }
};

#endif