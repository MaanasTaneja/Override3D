#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <fstream>
#include <sstream>

namespace Override
{

    class Shader
    {
    private:
        std::string m_vertfilepath;
        std::string m_fragfilepath;

        const char* m_vertex_source;	//OpenGL expects C style strings
        const char* m_fragment_source;

        unsigned int m_vert_shader;
        unsigned int m_frag_shader;

        unsigned int m_shader_program;
        void compile();
        void readfile();


    public:

        //REAFILE FUCNTION IS BROKEN DFOR SOME REASON? CANNOT TRANSFER DATA INTO MEMBER VARIABLES? IS IT BECUASE IM ACESSING MEMEBER VARIBALES DURING THE CREATION OF THE OBJECT?
        //NO BECUASE IT WORKS IF I DO THIS THING?

        Shader(const std::string& filevert, const std::string& filefrag) : m_vertfilepath{ filevert }, m_fragfilepath{ filefrag }, m_vertex_source{}, m_fragment_source{} {
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

            m_vertex_source = vertexCode.c_str();
            m_fragment_source = fragmentCode.c_str();

            compile();
        }

        Shader(const char* vertsource, const char* fragsource, bool t) : m_vertex_source{ vertsource }, m_fragment_source{ fragsource } { compile(); }

        unsigned int getshader() { return m_shader_program; }

        void setInteger(std::string name, int n);
        void setVector3(std::string name, glm::vec3 vector);
        void setVector4(std::string name, glm::vec4 vector);
        void setMatrix3(std::string name, glm::mat3 mat3);
        void setMatrix4(std::string name, glm::mat4 mat4);
    };
}