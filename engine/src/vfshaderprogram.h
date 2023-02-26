
#ifndef VFSHADERPROGRAM_H
#define VFSHADERPROGRAM_H
#include "shaderprogram.h"

namespace eng::rndr
{

class VFShaderProgram : public ShaderProgram
{
	public:
		VFShaderProgram(const std::string vertPath, const std::string fragPath);
		bool load() override;

	private:
		std::string m_vertPath, m_fragPath;
};
}
#endif // VFSHADERPROGRAM_H
