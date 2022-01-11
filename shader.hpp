#ifndef SHADER_HPP
#define SHADER_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<iostream>

class Shader{
    std::string getFileData(std::string path){
        std::ifstream fin;
        fin.open(path);
        std::string data = "", line;
        while (getline(fin, line)){
            data += line + '\n';
        }
        return data;
    }

    public:
    unsigned int ID;

    Shader(){}
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath){
        std::string vertexShaderSourceCode   = getFileData(vertexShaderPath);
        std::string fragmentShaderSourceCode = getFileData(fragmentShaderPath);
        const char* vertexShaderSource   = vertexShaderSourceCode.c_str();
        const char* fragmentShaderSource = fragmentShaderSourceCode.c_str();

        int success;
        char infoLog[1024];

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
            std::cerr << "Failed to compile vertex shader:\n" << infoLog << "\n";
        }
    
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
            std::cerr << "Failed to compile fragment shader:\n" << infoLog << "\n";
        }
    
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            std::cerr << "Failed to link program:\n" << infoLog << "\n";
        }
    
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Use(){
        glUseProgram(ID);
    }

    void Delete(){
        glDeleteProgram(ID);
    }
};

#endif