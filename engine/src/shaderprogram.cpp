
#include "shaderprogram.h"

namespace eng::rndr
{
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}

void ShaderProgram::bind()
{
	glUseProgram(m_program);
}

std::string ShaderProgram::ReadShaderFile(const std::string &path)
{
    std::string code;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        file.open(path);
        std::stringstream codeStream;
        codeStream << file.rdbuf();
        file.close();
        code = codeStream.str();
        
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr << "Unable to Load Shader File: " << path << std::endl;
    }
    return ProcessShaderCode(code);
}

GLuint ShaderProgram::LoadShader(const std::string &code, GLenum type)
{

    int success;
    char log[512];

    GLuint shader = glCreateShader(type);
    const char *cCode = code.c_str();
    glShaderSource(shader, 1, &cCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cerr << "Unable to compile shader: " << code << "Due to error: " << log << std::endl;
    }
    return shader;
}

std::string ShaderProgram::ProcessShaderCode(std::string code)//TODO make a proper version of this
{
    static const std::string incl = "#include";
    std::unordered_map<std::string, bool> included;
    size_t pos = code.find(incl);
    while (pos != std::string::npos)
    {
        size_t pathStart = pos + incl.length();
        while (code[pathStart] != '"') pathStart++;
        pathStart += 1;
        size_t pathEnd = pathStart;
        while (code[pathEnd] != '"' && pathEnd <= code.length()) pathEnd++;
        pathEnd += 1;
        if (pathEnd < code.length())
        {
            std::string path = code.substr(pathStart, pathEnd - pathStart - 1);
            if (!included.count(path))
            {
                std::string insCode = ReadShaderFile("../resources/shaders/" + path);
                code.insert(pos, insCode);
                included[path] = true;
            }
            else code.erase(pos, pathEnd - pos);
        }
       
        pos = code.find(incl);
    }
    return code;
}

void ShaderProgram::setUniform(const std::string name, GLint data)
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), data);
}
bool ShaderProgram::isLoaded() const
{
    return m_isLoaded;
}
void ShaderProgram::setUniform(const std::string name, glm::ivec2 data)
{
    glUniform2i(glGetUniformLocation(m_program, name.c_str()), data.x, data.y);
}
void ShaderProgram::setUniform(const std::string name, glm::ivec3 data)
{
    glUniform3i(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z);
}
void ShaderProgram::setUniform(const std::string name, glm::ivec4 data)
{
    glUniform4i(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z, data.w);
}
void ShaderProgram::setUniform(const std::string name, GLuint data)
{
    glUniform1ui(glGetUniformLocation(m_program, name.c_str()), data);
}
void ShaderProgram::setUniform(const std::string name, glm::uvec2 data)
{
    glUniform2ui(glGetUniformLocation(m_program, name.c_str()), data.x, data.y);
}
void ShaderProgram::setUniform(const std::string name, glm::uvec3 data)
{
    glUniform3ui(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z);
}
void ShaderProgram::setUniform(const std::string name, glm::uvec4 data)
{
    glUniform4ui(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z, data.w);
}
void ShaderProgram::setUniform(const std::string name, GLfloat data)
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), data);
}
void ShaderProgram::setUniform(const std::string name, glm::vec2 data)
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), data.x, data.y);
}
void ShaderProgram::setUniform(const std::string name, glm::vec3 data)
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z);
}
void ShaderProgram::setUniform(const std::string name, glm::vec4 data)
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), data.x, data.y, data.z, data.w);
}

void ShaderProgram::setUniform(const std::string name, glm::mat2 data)
{
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()),1, GL_FALSE, &data[0][0]);
}
void ShaderProgram::setUniform(const std::string name, glm::mat3 data)
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()),1, GL_FALSE, &data[0][0]);
}
void ShaderProgram::setUniform(const std::string name, glm::mat4 data)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()),1, GL_FALSE, &data[0][0]);
}
}
