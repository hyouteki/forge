#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../helper.hpp"

void LoadShader(const GLint programId,
				const GLenum shaderType,
				const std::string &programPath);
