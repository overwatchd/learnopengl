#version 330 core
layout (location = 0) in vec3 aPos; // λ�ñ���������λ��ֵΪ0

out vec4 vertexColor; // ΪƬ����ɫ��ָ��һ����ɫ���
uniform float ourRed;

void main()
{
    gl_Position = vec4(-aPos, 1.0); // ��ת��������
    vertexColor = vec4(ourRed, 0.0, 0.0, 1.0); // �������������Ϊ����ɫ
}
