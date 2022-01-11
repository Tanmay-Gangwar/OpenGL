#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<iostream>

class Texture{
    public:
    unsigned int ID;
    Texture(){}
    Texture(std::string path, int format, int repeat, int MinMagFilter){
        stbi_set_flip_vertically_on_load(true);
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, repeat);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinMagFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MinMagFilter);
    
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data){
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else std::cout << "Failed to load texture\n";
        stbi_image_free(data);
    }
    void Bind(){
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Delete(){
        glDeleteTextures(1, &ID);
    }
};

#endif