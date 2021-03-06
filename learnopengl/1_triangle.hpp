#pragma once
#include "common.h"

namespace triangle{

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

    const char* fragmentShaderSource_1 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.1f, 0.5f, 0.6f, 1.0f);\n"
        "}\0";

    int triangle_VAO(GLFWwindow* window, unsigned int shaderProgram)
    {
        float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
        };
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    int rectangle_EBO(GLFWwindow* window, unsigned int shaderProgram)
    {
        float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f,-0.5f, 0.0f,  // 右下角
       -0.5f,-0.5f, 0.0f, // 左下角
       -0.5f, 0.5f, 0.0f   // 左上角
        };
        unsigned int indices[] = { // 注意索引从0开始! 
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
        };
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        return 0;
    }

    // 练习题
    int two_triangle(GLFWwindow* window, unsigned int shaderProgram);
    int two_VAO_triangle(GLFWwindow* window, unsigned int shaderProgram);
    int two_color_VAO_triangle(GLFWwindow* window, unsigned int shaderProgram, unsigned int shaderProgram_1);

	int enter(GLFWwindow* window)
	{
		unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		if (!shaderProgram)
			return -1;
        unsigned int shaderProgram_1 = CreateShaderProgram(vertexShaderSource, fragmentShaderSource_1);
        if (!shaderProgram_1)
            return -1;

        //return triangle_VAO(window, shaderProgram);
        //return rectangle_EBO(window, shaderProgram);
        //return two_triangle(window, shaderProgram);
        //return two_VAO_triangle(window, shaderProgram);
        return two_color_VAO_triangle(window, shaderProgram, shaderProgram_1);
	}

    int two_triangle(GLFWwindow* window, unsigned int shaderProgram)
    {
        // 两个相连的三角
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.25f, 0.5f, 0.0f,
             0.0f, -0.5f, 0.0f,
             0.25f, 0.5f, 0.0f, // 增加两个点
             0.5f, -0.5f, 0.0f
        };
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDrawArrays(GL_TRIANGLES, 2, 3);   // 第二个三角的起始索引为2，还是画三个点

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;

    }

    int two_VAO_triangle(GLFWwindow* window, unsigned int shaderProgram)
    {
        // 使用两个VAO画两个三角
        // 想将获取VAO封装为函数，但失败了，直接复制了两份代码
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.25f, 0.5f, 0.0f,
             0.0f, -0.5f, 0.0f,
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        float vertices_1[] = {
             0.5f,  0.5f, 0.0f,
             0.25f,-0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        unsigned int VBO_1;
        glGenBuffers(1, &VBO_1);
        unsigned int VAO_1;
        glGenVertexArrays(1, &VAO_1);

        glBindVertexArray(VAO_1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(VAO_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;

    }

    int two_color_VAO_triangle(GLFWwindow* window, unsigned int shaderProgram, unsigned int shaderProgram_1)
    {
        // 使用两个VAO画两个三角
        // 想将获取VAO封装为函数，但失败了，直接复制了两份代码
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.25f, 0.5f, 0.0f,
             0.0f, -0.5f, 0.0f,
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        float vertices_1[] = {
             0.5f,  0.5f, 0.0f,
             0.25f,-0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,
        };

        unsigned int VBO_1;
        glGenBuffers(1, &VBO_1);
        unsigned int VAO_1;
        glGenVertexArrays(1, &VAO_1);

        glBindVertexArray(VAO_1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glUseProgram(shaderProgram_1);
            glBindVertexArray(VAO_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;

    }

}
