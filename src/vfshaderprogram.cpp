
#include "vfshaderprogram.h"

namespace eng::rndr
{
VFShaderProgram::VFShaderProgram(const std::string vertPath, const std::string fragPath) : m_vertPath(vertPath), m_fragPath(fragPath)
{

}
bool VFShaderProgram::load()
{
    m_program = glCreateProgram();
	GLuint vertId = LoadShader(ReadShaderFile(m_vertPath), GL_VERTEX_SHADER);
    GLuint fragId = LoadShader(ReadShaderFile(m_fragPath), GL_FRAGMENT_SHADER);
	glAttachShader(m_program, vertId);
    glAttachShader(m_program, fragId);
    glLinkProgram(m_program);
    int success;
    char log[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_program, 512, NULL, log);
        std::cerr << "Unable to compile shader: " << log << std::endl;
        return false;
    }
    glDeleteShader(fragId);
    glDeleteShader(vertId);
	return true;
}   
}