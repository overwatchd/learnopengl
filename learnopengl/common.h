#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

void processInput(GLFWwindow* window);
unsigned int CreateShaderProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);

#endif
