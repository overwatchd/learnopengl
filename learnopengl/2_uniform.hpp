#pragma once
#include "common.h"

namespace uniform {

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = ourColor;\n"
        "}\n";

    const char* vertexShaderSource_1 = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0";

    const char* fragmentShaderSource_1 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(ourColor, 1.0);\n"
        "}\n";

    int triangle_Uniform(GLFWwindow* window)
    {
        // 变色三角
        float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
        };

        unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
        if (!shaderProgram)
            return -1;

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

            float timeValue = float(glfwGetTime());
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    int triangle_three_color(GLFWwindow* window)
    {
        // 三色三角
        float vertices[] = {
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
        };

        unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource_1, fragmentShaderSource_1);
        if (!shaderProgram)
            return -1;

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float timeValue = float(glfwGetTime());
            float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
            int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
            glUseProgram(shaderProgram);
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    // 练习
    int updown_vertex(GLFWwindow* window);  // 顶点让三角倒立
    int move_vertex(GLFWwindow* window);  // 让三角动起来
    int move_color_vertex(GLFWwindow* window);  // 让三角动起来

    int enter(GLFWwindow* window)
    {
        //return triangle_Uniform(window);
        //return triangle_three_color(window);
        //return updown_vertex(window);
        //return move_vertex(window);
        return move_color_vertex(window);
    }

    int updown_vertex(GLFWwindow* window)
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

        Shader shader = Shader("./updown.vert", "./vert_color.frag");

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float timeValue = float(glfwGetTime());
            float redValue = (sin(timeValue) / 2.0f) + 0.5f;
            shader.use();
            shader.setFloat("ourRed", redValue);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    int move_vertex(GLFWwindow* window)
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

        Shader shader = Shader("./move.vert", "./vert_color.frag");

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float timeValue = float(glfwGetTime());
            float xShift = sin(timeValue);
            shader.use();
            shader.setFloat("xShift", xShift);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    int move_color_vertex(GLFWwindow* window)
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

        Shader shader = Shader("./pos_color.vert", "./pos_color.frag");

        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            float timeValue = float(glfwGetTime());
            float xShift = sin(timeValue);
            shader.use();
            shader.setFloat("xShift", xShift);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}
