#version 330

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition;
uniform vec3 camPosition;

void main() {
    vec4 worldPosition = transform * vec4(position, 1.0);
    gl_Position = projection * transform * vec4(position, 1.0);
    pass_textureCoords = textureCoords;
    
    surfaceNormal = (transform * vec4(normal, 0.0)).xyz;
    toLightVector = lightPosition - camPosition.xyz;
    toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}

