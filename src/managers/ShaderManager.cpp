#include "ShaderManager.hpp"

auto ShaderManager::getID() const noexcept {
	return ID;
}
void ShaderManager::use() const noexcept {
	glUseProgram(ID);
}
void ShaderManager::setBool(std::string_view name, bool value) const noexcept {
	glUniform1i(glGetUniformLocation(ID, name.data()), (int) value);
}
void ShaderManager::setInt(std::string_view name, int value) const noexcept {
	glUniform1i(glGetUniformLocation(ID, name.data()), value);
}
void ShaderManager::setFloat(std::string_view name, float value) const noexcept {
	glUniform1f(glGetUniformLocation(ID, name.data()), value);
}
void ShaderManager::setVec3(std::string_view name, const glm::vec3 &value) const noexcept {
	glUniform3fv(glGetUniformLocation(ID, name.data()), 1, glm::value_ptr(value));
}
void ShaderManager::setMat3(std::string_view name, const glm::mat3 &value) const noexcept {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderManager::setMat4(std::string_view name, const glm::mat4 &value) const noexcept {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}

ShaderManager::ShaderManager(std::string_view vertexFileName, std::string_view fragmentFileName) {

	const GLuint vertex =
		createShader(GL_VERTEX_SHADER, readShaderFile(shaderFolder + '/' + vertexFileName.data()), shaderType::VERTEX);
	const GLuint fragment =
		createShader(GL_FRAGMENT_SHADER, readShaderFile(shaderFolder + '/' + fragmentFileName.data()), shaderType::FRAGMENT);

	// create program and link shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, shaderType::PROGRAM);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void ShaderManager::checkCompileErrors(const GLuint shader, shaderType type) const {
	GLint success;
	GLchar infoLog[1024];
	if (type != shaderType::PROGRAM) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream errorMessage;
			errorMessage << "ERROR::SHADER_COMPILATION_ERROR " << static_cast<int>(type) << "\n"
						 << infoLog << "\n -- --------------------------------------------------- -- ";

			throw std::runtime_error {errorMessage.str()};
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream errorMessage;
			errorMessage << "ERROR::SHADER_COMPILATION_ERROR " << static_cast<int>(type) << "\n"
						 << infoLog << "\n -- --------------------------------------------------- -- ";

			throw std::runtime_error {errorMessage.str()};
		}
	}
}
std::string ShaderManager::readShaderFile(std::string_view path) const {
	std::string code;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	// read files
	try {
		file.open(path.data());
		code = std::string {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
		file.close();
	} catch (std::ifstream::failure e) {
		throw std::runtime_error {
			(std::string {e.what()} + "\nERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\nPath: " + path.data())};
	}
	return code;
}
GLuint ShaderManager::createShader(const GLenum GLtype, std::string_view code, shaderType type) const {
	const GLuint shader {glCreateShader(GLtype)};
	const char *codePointer = code.data();
	glShaderSource(shader, 1, &codePointer, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, type);
	return shader;
}