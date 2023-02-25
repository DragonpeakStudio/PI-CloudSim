
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace eng::rndr
{
class ShaderProgram
{
	public:

		~ShaderProgram();
		virtual bool load() = 0;
		virtual void bind();

		void setUniform(const std::string name, GLfloat data);
        void setUniform(const std::string name, glm::vec2 data);
        void setUniform(const std::string name, glm::vec3 data);
        void setUniform(const std::string name, glm::vec4 data);

        void setUniform(const std::string name, GLint data);
        void setUniform(const std::string name, glm::ivec2 data);
        void setUniform(const std::string name, glm::ivec3 data);
        void setUniform(const std::string name, glm::ivec4 data);

        void setUniform(const std::string name, GLuint data);
        void setUniform(const std::string name, glm::uvec2 data);
        void setUniform(const std::string name, glm::uvec3 data);
        void setUniform(const std::string name, glm::uvec4 data);

        void setUniform(const std::string name, glm::mat2 data);
        void setUniform(const std::string name, glm::mat3 data);
        void setUniform(const std::string name, glm::mat4 data);

	protected:
		std::string ReadShaderFile(const std::string& path);
        std::string ProcessShaderCode(std::string code);
        GLuint LoadShader(const std::string& code, GLenum type);
		GLuint m_program = 0;

};
}
#endif // SHADERPROGRAM_H
