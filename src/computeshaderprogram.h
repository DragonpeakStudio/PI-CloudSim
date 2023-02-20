#ifndef COMPUTESHADERPROGRAM_H
#define COMPUTESHADERPROGRAM_H
#include "shaderprogram.h"


class ComputeShaderProgram : public ShaderProgram
{
    public:
        ComputeShaderProgram(const std::string path);
        bool load() override;
        void dispatch(glm::uvec3 workGroups);

    private:
        std::string m_path;
};

#endif // COMPUTESHADERPROGRAM_H
