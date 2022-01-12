#ifndef SPRING_HPP
#define STRING_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shader.hpp"
#include"buffer.hpp"
#include"camera.hpp"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<cmath>
#include<vector>
#include"shader.hpp"
#include"buffer.hpp"

class Spring{
    public:
    const float PI = acos(-1.0f);
    glm::vec3 position;
    float length = 1.0f;
    int linear_point_cnt = 1000;
    int circular_point_cnt = 10;
    int number_spirals = 20;
    float radius = 0.2f;
    Shader shader;
    unsigned int VBO, VAO;
    glm::mat4 model = glm::mat4(1.0f);
    float k;
    Spring(glm::vec3 position, float length, float k){
        std::vector<float> vertices;
        float theta = 0.0f;
        float x = 0.0f;
        float delta_x = 1.0f / (linear_point_cnt - 1);
        float delta_theta = (2 * PI * number_spirals) / (linear_point_cnt - 1);
        for (int i = 0; i < linear_point_cnt - 1; i++){
            vertices.push_back(x);
            vertices.push_back(radius * sin(theta));
            vertices.push_back(radius * cos(theta));
            x += delta_x;
            theta += delta_theta;
            vertices.push_back(x);
            vertices.push_back(radius * sin(theta));
            vertices.push_back(radius * cos(theta));
        }
        shader = Shader("spring.vert", "spring.frag");
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        this->length = length;
        this->position = position;
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        this->k = k;
    }

    void draw(glm::mat4 &view, glm::mat4 &projection){
        glLineWidth(1.0f);
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniform1f(glGetUniformLocation(shader.ID, "length"), length);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2 * linear_point_cnt);
    }

};

#endif