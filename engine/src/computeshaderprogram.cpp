#include "computeshaderprogram.h"
namespace eng::rndr
{
ComputeShaderProgram::ComputeShaderProgram(const std::string path) : m_path(path)
{

}

bool ComputeShaderProgram::load()
{
    if(m_isLoaded)return true;
    m_isLoaded = true;
    m_program = glCreateProgram();
    GLuint shaderId = LoadShader(ReadShaderFile(m_path), GL_COMPUTE_SHADER);
    glAttachShader(m_program, shaderId);
    glLinkProgram(m_program);
    int success;
    char log[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_program, 512, NULL, log);
        std::cerr << "Unable to compile shader: " << log << std::endl;
        m_isLoaded = false;

        return false;
    }
    glDeleteShader(shaderId);
    return true;
}

void ComputeShaderProgram::dispatch(glm::uvec3 workGroups)
{
    bind();
    glDispatchCompute(workGroups.x, workGroups.y, workGroups.z);
	glUseProgram(0);
    
}
}
