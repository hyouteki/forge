#include "shader.hpp"

static const char *LoadProgram(const std::string &programPath) {
	std::ifstream file(programPath, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << FunLoc << std::endl << "error: could not open file '"
				  << programPath << "'" << std::endl;
		exit(EXIT_FAILURE);
	}

	file.seekg(0, std::ios::end);
	size_t programSize = file.tellg();
	file.seekg(0, std::ios::beg);

	char *buffer = new char[programSize+1];
	if (!buffer) {
		std::cerr << FunLoc << std::endl << "error: "
				  << "failed to allocate memory" << std::endl;
		exit(EXIT_FAILURE);
    }

	file.read(buffer, programSize);
	buffer[programSize] = 0;
	file.close();
	return buffer;
}

void LoadShader(const GLint programId,
				const GLenum shaderType,
				const std::string &programPath) {
	GLuint shaderId = glCreateShader(shaderType);
	const char *shaderProgram = LoadProgram(programPath);
	glShaderSource(shaderId, 1, &shaderProgram, nullptr);
	glCompileShader(shaderId);

	GLint result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(sizeof(char)*length);
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cerr << FunLoc << std::endl
				  << "info: failed to compile shader '" << programPath
				  << "'" << std::endl << "error: " << message << std::endl;
		exit(EXIT_FAILURE);
	}

	glAttachShader(programId, shaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);
	glDeleteShader(shaderId);
}
