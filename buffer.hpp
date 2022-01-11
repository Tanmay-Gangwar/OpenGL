// #ifndef BUFFER_HPP
// #define BUFFER_HPP

// #include<glad/glad.h>
// #include<GLFW/glfw3.h>
// #include<vector>

// class Buffer{
//     public:
//     unsigned int VAO, VBO, EBO;
//     float* vertices;
//     unsigned int* indices;
//     GLsizeiptr verticesSize, indicesSize;
//     Buffer(){}
//     Buffer(float* vertices, GLsizeiptr verticesSize, unsigned int* indices, GLsizeiptr indicesSize, std::vector<int> vertex_data){
//         this->vertices = vertices;
//         this->indices = indices;
//         this->verticesSize = verticesSize;
//         this->indicesSize = indicesSize;
//         glGenVertexArrays(1, &VAO);
//         glGenBuffers(1, &VBO);
//         glGenBuffers(1, &EBO);

//         glBindVertexArray(VAO);
//         glBindBuffer(GL_ARRAY_BUFFER, VBO);
//         glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

//         int total = 0;
//         for (int x: vertex_data) total += x;
//         for (int i = 0, sum = 0; i < vertex_data.size(); sum += vertex_data[i], i++){
//             glVertexAttribPointer(i, vertex_data[i], GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(sum * sizeof(float)));
//             glEnableVertexAttribArray(i);
//         }
//     }

//     void Bind(){
//         glBindVertexArray(VAO);
//     }

//     void Unbind(){
//         glBindVertexArray(0);
//     }

//     void Delete(){
//         glDeleteVertexArrays(1, &VAO);
//         glDeleteBuffers(1, &VBO);
//         glDeleteBuffers(1, &EBO);
//     }

//     void DrawTriangles(){
//         glDrawElements(GL_TRIANGLES, indicesSize / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
//     }
// };

// #endif

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>

class Buffer{
    public:
    unsigned int VAO, VBO, EBO;
    // float* vertices;
    // unsigned int* indices;
    // GLsizeiptr verticesSize, indicesSize;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    Buffer(){}
    Buffer(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<int> vertex_data){
        this->vertices = vertices;
        this->indices = indices;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

        int total = 0;
        for (int x: vertex_data) total += x;
        for (int i = 0, sum = 0; i < vertex_data.size(); sum += vertex_data[i], i++){
            glVertexAttribPointer(i, vertex_data[i], GL_FLOAT, GL_FALSE, total * sizeof(float), (void*)(sum * sizeof(float)));
            glEnableVertexAttribArray(i);
        }
    }

    void Bind(){
        glBindVertexArray(VAO);
    }

    void Unbind(){
        glBindVertexArray(0);
    }

    void Delete(){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void DrawTriangles(){
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
};

#endif