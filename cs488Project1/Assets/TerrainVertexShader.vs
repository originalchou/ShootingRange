#version 330

in vec3 position;
in vec2 textureCoords;
in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out float visibility;


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 lightPosition;

const float density = 0.009;
const float gradient = 0.5;

void main() {
    vec4 worldPosition = transform * vec4(position, 1.0);
    vec4 positionToCam = view * worldPosition;
    gl_Position = projection * view * transform * vec4(position, 1.0);
    pass_textureCoords = textureCoords * 20;
    
    surfaceNormal = (transform * vec4(normal, 0.0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
    toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
    
    float dis = length(positionToCam.xyz);
    visibility = exp(-pow((dis * density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
