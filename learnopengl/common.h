#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

void processInput(GLFWwindow* window);
unsigned int CreateShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);

#endif
