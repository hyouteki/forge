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
    
    // Setting up vertex buffers and attrib arrays
    float positions[6] = {
         0.0f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
    };

	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    // Render loop
    while (!glfwWindowShouldClose(window)) {

		// Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
		}

		// Drawing
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexBufferId);
    glfwTerminate();
    return EXIT_SUCCESS;
}
