#version 330

in vec3 position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 view;

void main(){
    gl_Position = projectionMatrix * view * vec4(position, 1.0);
    textureCoords = position;
}
