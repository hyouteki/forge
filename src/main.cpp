#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "helper.hpp"
#include "constants.hpp"
#include "graphics/shader.hpp"

int main() {

	// Setup
    if (!glfwInit()) {
		std::cerr << FunLoc << std::endl << "error: "
				  << "failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
	
    GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);
    if (!window) {
		std::cerr << FunLoc << std::endl << "error: "
				  << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
	
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
		std::cerr << FunLoc << std::endl << "error: "
				  << "failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Build and compile the shader program
	GLuint shaderProgram = glCreateProgram();
	LoadShader(shaderProgram, GL_VERTEX_SHADER, "./shaders/vshader.glsl");
	LoadShader(shaderProgram, GL_FRAGMENT_SHADER, "./shaders/fshader.glsl");
    
    // Set up vertex data and buffers and configure vertex attributes
    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}
