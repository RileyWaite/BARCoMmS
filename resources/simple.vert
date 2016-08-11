#version 330 core

#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec4 vColor;
out vec2 sameTexCoord;
out float sameContrast;
out float sameBrightness;
out float sameWidth;
out float sameHeight;

layout(location = 3)  uniform float rTint;
layout(location = 4)  uniform float gTint;
layout(location = 5)  uniform float bTint;
layout(location = 6)  uniform float contrast;
layout(location = 7)  uniform float brightness;
layout(location = 8)  uniform mat4 projectionMatrix;
layout(location = 9)  uniform mat4 modelViewMatrix;
layout(location = 10) uniform float width;
layout(location = 11) uniform float height;

void main(void)
{
    // vColor = vec4(color, 1.0);
    vColor = vec4(rTint,gTint,bTint,1.0);
    sameContrast = contrast;
    sameBrightness = brightness;
    sameWidth = width;
    sameHeight = height;

    gl_Position = vec4(position, 1.0);
    sameTexCoord = texCoord;
}
