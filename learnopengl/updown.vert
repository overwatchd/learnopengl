#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0

out vec4 vertexColor; // 为片段着色器指定一个颜色输出
uniform float ourRed;

void main()
{
    gl_Position = vec4(-aPos, 1.0); // 翻转整个坐标
    vertexColor = vec4(ourRed, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色
}
