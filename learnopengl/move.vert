#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;
uniform float xShift;

void main()
{
    gl_Position = vec4(aPos.x + xShift, aPos.yz, 1.0);
    vertexColor = vec4(0.0, 0.8, 0.8, 1.0);
}
