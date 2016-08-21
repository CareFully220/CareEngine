#include "Shader.h"
#include "ErrorHandler.h"
#include <iostream>
#include <fstream>

namespace CareEngine {

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& fileName);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);

	Shader::Shader(const std::string& fileName)
	{
		m_program = glCreateProgram();
		m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.shd"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(fileName + ".fs.shd"), GL_FRAGMENT_SHADER);

		for (unsigned int i = 0; i < NUM_SHADERS; i++)
		{
			glAttachShader(m_program, m_shaders[i]);
		}

		glBindAttribLocation(m_program, 0, "position");
		glBindAttribLocation(m_program, 1, "texCoord");
		glBindAttribLocation(m_program, 2, "normal");

		glLinkProgram(m_program);
		CheckShaderError(m_program, GL_LINK_STATUS, true, "Program linking failed");

		glValidateProgram(m_program);
		CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program invalid");

		m_uniforms[TRANSFORM_U] = getUniformLocation("transform");
	}

	GLuint Shader::getUniformLocation(const std::string& uniformName)
	{
		GLuint location = glGetUniformLocation(m_program, "transform");
		if (location == GL_INVALID_INDEX)
		{
			ErrorHandler::sendError(ErrorHandler::ERR_FATAL, "Shader", "Uniform " + uniformName + " not found in shader!");
		}
		return location;
	}

	void Shader::Bind()
	{
		glUseProgram(m_program);
	}

	Shader::~Shader()
	{
		for (unsigned int i = 0; i < NUM_SHADERS; i++)
		{
			glDetachShader(m_program, m_shaders[i]);
			glDeleteShader(m_shaders[i]);
		}
		glDeleteProgram(m_program);
	}

	void Shader::Update(const Transform& transform, const Camera& camera)
	{
		glm::mat4 Model = camera.getViewProjection() * transform.getModel();
		glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &Model[0][0]);
	}

	static GLuint CreateShader(const std::string& text, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);
		if (shader == 0)
			ErrorHandler::sendError(ErrorHandler::ERR_FATAL, "Shader", "Shader creation failed");

		const GLchar* shaderSourceStrings[1];
		GLint shaderSourceStringLenghts[1];
		shaderSourceStrings[0] = text.c_str();
		shaderSourceStringLenghts[0] = (GLint)text.length();

		glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLenghts);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compile failed");

		return shader;
	}

	static std::string LoadShader(const std::string& fileName)
	{
		std::ifstream file;
		file.open(fileName.c_str());

		std::string output;
		std::string line;

		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				output.append(line + "\n");
			}
		}
		else
		{
			ErrorHandler::sendError(ErrorHandler::ERR_FATAL, "Shader", "Failed to load shader " + fileName);
		}
		return output;
	}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE) {
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			ErrorHandler::sendError(ErrorHandler::ERR_FATAL, "Shader - " + errorMessage, error);
		}
	}

}