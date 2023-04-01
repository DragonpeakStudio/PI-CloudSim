#include "cloudfluidsimulator.h"

CloudFluidSimulator::CloudFluidSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale) : CloudSimulator(bbox, voxelScale), 
m_velocity(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGB, 1, GL_RGB16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_qvAndTemp(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RG, 1, GL_RG16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_qc(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_R, 1, GL_R16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_pressureAndDivergence(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RG, 1, GL_RG16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_advect("../resources/shaders/advect.comp"),
m_applyForces("../resources/shaders/applyforces.comp"),
m_updateWaterAndTemp("../resources/shaders/m_updatewaterandtemp.comp"),
m_calcDivergence("../resources/shaders/calcdivergence.comp"),
m_pressureItr("../resources/shader/prerssureitr.comp"),
m_applyPressureGrad("../resources/shaders/applypressuregrad.comp")
{

}

CloudFluidSimulator::~CloudFluidSimulator()
{

}

void CloudFluidSimulator::update(double delta)
{
    //{//advect.comp, just use basic advection for now, maybe add MacCormack advection in future
        //Advect quantities
    //}
    //{//applyforces.comp
        //compute buoyant force

        //compute vorticity confinement

        //apply buoyant force & vorticity confinement+

        //apply free slip

    //}
    //{//updatetempandwater.comp
        //update qc,qv

        //update temp
    //}
    //{//calcdivergence.comp
        //compute divergence
    //}
    //{//pressureitr.comp
        //compute pressure, accounting for boundaries
    //}
    //{//applypressuregrad.comp
        //apply pressure gradient
    //}
}

void CloudFluidSimulator::setCollisionField(std::unique_ptr<eng::rndr::Texture3d> collisionField)
{
    m_collisionField = std::move(collisionField);
}

eng::rndr::Texture3d &CloudFluidSimulator::getField(std::string_view identifier)
{
    // TODO: insert return statement here
}

void CloudFluidSimulator::drawUI()
{

}