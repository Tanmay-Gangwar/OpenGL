#version 330 core
layout (location = 0) in vec3 aPos;

uniform float length;
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

void main(){
    gl_Position = projection * view * model * vec4(aPos.x * length, aPos.y, aPos.z, 1.0f);
}