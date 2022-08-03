#include "Shader.h"
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

namespace Override
{
	void Shader::compile()
	{
		m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vert_shader, 1, &m_vertex_source, NULL);
		glCompileShader(m_vert_shader);


		char log[1024];
		GLint isCompiled = 0;


		glGetShaderiv(m_vert_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(m_vert_shader, 1024, NULL, log);
			std::cout << "Vertex shader compilation failed! : " << m_vertfilepath << ":  " << log << "\n";

			glDeleteShader(m_vert_shader);
			return;
		}


		m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_frag_shader, 1, &m_fragment_source, NULL);
		glCompileShader(m_frag_shader);

		isCompiled = 0;
		glGetShaderiv(m_frag_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(m_frag_shader, 1024, NULL, log);
			std::cout << "Fragment shader compilation failed! : " << m_fragfilepath << ":  " << log << "\n";

			glDeleteShader(m_frag_shader);
			return;
		}


		m_shader_program = glCreateProgram();
		glAttachShader(m_shader_program, m_vert_shader);
		glAttachShader(m_shader_program, m_frag_shader);
		glLinkProgram(m_shader_program);

		int isLinked = 0;
		glGetProgramiv(m_shader_program, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_shader_program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			char infoLog[1024];
			glGetProgramInfoLog(m_shader_program, maxLength, &maxLength, infoLog);


			std::cout << "Shader program linking failed! : " << infoLog << "\n";
			glDeleteProgram(m_shader_program);
			// Don't leak shaders either.
			glDeleteShader(m_vert_shader);
			glDeleteShader(m_frag_shader);
		}

		glDetachShader(m_shader_program, m_vert_shader);
		glDetachShader(m_shader_program, m_frag_shader);
	}

	void Shader::readfile()
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(m_vertfilepath);
			fShaderFile.open(m_fragfilepath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Shader Not succesfully read! : " << m_fragfilepath << std::endl;
		}



		Shader::m_vertex_source = vertexCode.c_str();
		Shader::m_fragment_source = fragmentCode.c_str();

	}

	void Shader::setMatrix4(std::string name, glm::mat4 mat4)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
	}
	void Shader::setMatrix3(std::string name, glm::mat3 mat3)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, GL_FALSE, &mat3[0][0]);
	}
	void Shader::setVector3(std::string name, glm::vec3 vector)
	{
		glUniform3fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, &vector[0]);
	}
	void Shader::setVector4(std::string name, glm::vec4 vector)
	{
		glUniform4fv(glGetUniformLocation(m_shader_program, name.c_str()), 1, &vector[0]);
	}
	void Shader::setInteger(std::string name, int n)
	{
		glUniform1i(glGetUniformLocation(m_shader_program, name.c_str()), n);
	}
}