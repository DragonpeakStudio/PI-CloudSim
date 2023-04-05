#include "cloudfluidsimulator.h"

CloudFluidSimulator::CloudFluidSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale) : CloudSimulator(bbox, voxelScale), 
m_velocity(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 4, GL_RGBA16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),//This has to be 4 components because  computes shaders cannot write to 3 component iamges for some reason
m_qvAndTemp(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RG, 2, GL_RG16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_qc(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RG, 2, GL_RG16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_pressureAndDivergence(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RG, 2, GL_RG16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_advect("../resources/shaders/advect.comp"),
m_applyForces("../resources/shaders/applyforces.comp"),
m_updateWaterAndTemp("../resources/shaders/updatewaterandtemp.comp"),
m_calcDivergence("../resources/shaders/calcdivergence.comp"),
m_pressureItr("../resources/shaders/pressureitr.comp"),
m_applyPressureGrad("../resources/shaders/applypressuregrad.comp"),
m_initProcess("../resources/shaders/initfields.comp"),
m_velSlicer(m_velocity.getActive()),
m_qvAndTempSlicer(m_qvAndTemp.getActive()),
m_qcSlicer(m_qc.getActive()),
m_pressureAndDivergenceSlicer(m_pressureAndDivergence.getActive())

{
    m_advect.load();
    m_applyForces.load();
    m_updateWaterAndTemp.load();
    m_calcDivergence.load();
    m_pressureItr.load();
    m_applyPressureGrad.load();
    m_initProcess.load();
}

CloudFluidSimulator::~CloudFluidSimulator()
{
}

void CloudFluidSimulator::update(double delta)
{
    //{//advect.comp, just use basic advection for now, maybe add MacCormack advection in future
        //Advect quantities
    advectField(m_qvAndTemp, m_velocity.getNonActive(), delta);
    advectField(m_qc, m_velocity.getNonActive(), delta);
    advectField(m_velocity, m_velocity.getNonActive(), delta);

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
    //}
    //{//applyforces.comp
        //compute buoyant force
        //compute vorticity confinement
        //apply buoyant force & vorticity confinement+
        //apply free slip
    m_applyForces.bind();
    m_velocity.getNonActive().bind(GL_TEXTURE1);
    m_applyForces.setUniform("delta", (float)delta);
    m_applyForces.setUniform("inVelField", 1);
    m_applyForces.setUniform("outVelField", 0);
    glBindImageTexture(0, m_velocity.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_velocity.getActive().info().internalFormat);

    m_applyForces.dispatch(glm::uvec3(m_velocity.getActive().width()/8, m_velocity.getActive().height()/8, m_velocity.getActive().depth()/8));

    m_velocity.swap();

    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
    //}
    //{//updatetempandwater.comp
        //update qc,qv
        //update temp
    m_updateWaterAndTemp.bind();
    m_updateWaterAndTemp.setUniform("delta", (float)delta);
    m_updateWaterAndTemp.setUniform("outqvAndTemp", 0);
    m_updateWaterAndTemp.setUniform("outqc", 1);
    m_updateWaterAndTemp.setUniform("inqvAndTemp", 2);
    m_updateWaterAndTemp.setUniform("inqc", 3);
    m_qvAndTemp.getNonActive().bind(GL_TEXTURE2);
    m_qc.getNonActive().bind(GL_TEXTURE3);
    glBindImageTexture(0, m_qvAndTemp.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_qvAndTemp.getActive().info().internalFormat);
    glBindImageTexture(1, m_qc.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_qc.getActive().info().internalFormat);
    m_updateWaterAndTemp.dispatch(glm::uvec3(m_qc.getActive().width()/8, m_qc.getActive().height()/8, m_qc.getActive().depth()/8));
    m_qc.swap();
    m_qvAndTemp.swap();

    //}
    //{//calcdivergence.comp
        //compute divergence
    m_calcDivergence.bind();
    m_calcDivergence.setUniform("outPressureAndDivergence", 0);
    m_calcDivergence.setUniform("inVelocity", 1);
    m_velocity.getNonActive().bind(GL_TEXTURE1);
    glBindImageTexture(0, m_pressureAndDivergence.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_pressureAndDivergence.getActive().info().internalFormat);
    m_calcDivergence.dispatch(glm::uvec3(m_pressureAndDivergence.getActive().width()/8, m_pressureAndDivergence.getActive().height()/8, m_pressureAndDivergence.getActive().depth()/8));
    m_pressureAndDivergence.swap();
    //}
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);

    //{//pressureitr.comp basic jacobbi for now
        //compute pressure, accounting for boundaries
    m_pressureItr.bind();
    m_pressureItr.setUniform("outPressureAndDivergence", 0);
    m_pressureItr.setUniform("inPressureAndDivergence", 1);
    for(unsigned int i = 0; i < m_pressureItrs; i++)
    {
        m_pressureAndDivergence.getNonActive().bind(GL_TEXTURE1);
        glBindImageTexture(0, m_pressureAndDivergence.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_pressureAndDivergence.getActive().info().internalFormat);
        m_pressureItr.dispatch(glm::uvec3(m_pressureAndDivergence.getActive().width()/8, m_pressureAndDivergence.getActive().height()/8, m_pressureAndDivergence.getActive().depth()/8));
        m_pressureAndDivergence.swap();
    }
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
    //}
    //{//applypressuregrad.comp
        //apply pressure gradient
    m_applyPressureGrad.bind();
    m_applyPressureGrad.setUniform("outVelocity", 0);
    m_applyPressureGrad.setUniform("inVelocity", 1);
    m_applyPressureGrad.setUniform("inPressureAndDivergence", 2);
    m_velocity.getNonActive().bind(GL_TEXTURE1);
    m_pressureAndDivergence.getNonActive().bind(GL_TEXTURE2);
    glBindImageTexture(0, m_velocity.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_velocity.getActive().info().internalFormat);
    m_applyPressureGrad.dispatch(glm::uvec3(m_velocity.getActive().width()/8, m_velocity.getActive().height()/8, m_velocity.getActive().depth()/8));
    m_velocity.swap();
    //}
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);

}
void CloudFluidSimulator::setCollisionField(std::unique_ptr<eng::rndr::Texture3d> collisionField)
{
    m_collisionField = std::move(collisionField);
}

void CloudFluidSimulator::advectField(Swappable3DTexture &field, eng::rndr::Texture3d &velField, float delta)
{
    m_advect.bind();
    m_advect.setUniform("delta", delta);
    field.getNonActive().bind(GL_TEXTURE1);
    velField.bind(GL_TEXTURE2);
    m_advect.setUniform("outField", 0);
    m_advect.setUniform("inField", 1);
    m_advect.setUniform("velocityField", 2);
    glBindImageTexture(0, field.getActive().id(), 0, false, 0, GL_WRITE_ONLY, field.getActive().info().internalFormat);
    m_advect.dispatch(glm::uvec3(field.getActive().width()/8, field.getActive().height()/8, field.getActive().depth()/8));
    field.swap();
}

void CloudFluidSimulator::initFields()
{
    m_initProcess.bind();
    m_initProcess.setUniform("outVelocity", 0);
    m_initProcess.setUniform("outqc", 1);
    m_initProcess.setUniform("outqvAndTemp", 2);
    glBindImageTexture(0, m_velocity.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_velocity.getActive().info().internalFormat);
    glBindImageTexture(1, m_qc.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_qc.getActive().info().internalFormat);
    glBindImageTexture(2, m_qvAndTemp.getActive().id(), 0, false, 0, GL_WRITE_ONLY, m_qvAndTemp.getActive().info().internalFormat);

    m_initProcess.dispatch(glm::uvec3(m_velocity.getActive().width()/8, m_velocity.getActive().height()/8, m_velocity.getActive().depth()/8));
    m_velocity.swap();
    m_qc.swap();
    m_qvAndTemp.swap();
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);

}

eng::rndr::Texture3d &CloudFluidSimulator::getField(std::string_view identifier)
{
    if(identifier=="density")
    {
        return m_qc.getActive();
    }
    else if (identifier=="velocity")
    {
        return m_velocity.getActive();
    }
    else if (identifier=="qvAndTemp")
    {
        return m_qvAndTemp.getActive();
    }
    else if(identifier=="pressureAndDivergence")
    {
        return m_pressureAndDivergence.getActive();
    }
    throw std::runtime_error("CloudFluidSimulator::getField - Invalid Field: " + std::string(identifier));
}

void CloudFluidSimulator::drawUI()
{

    ImGui::Begin("Fluid Sim");
    ImGui::SliderInt("Slice", &m_debugSlice, 0, m_qc.getActive().depth());
    m_velSlicer.update(m_debugSlice);
    ImGui::LabelText("Velocity:", "");
    ImGui::Image((void*)(intptr_t)m_velSlicer.getSlice()->id(), {(float)128.f, (float)128.f});
    m_qcSlicer.update(m_debugSlice);
    ImGui::LabelText("qc:", "");

    ImGui::Image((void*)(intptr_t)m_qcSlicer.getSlice()->id(), {(float)128.f, (float)128.f});
    m_qvAndTempSlicer.update(m_debugSlice);
    ImGui::LabelText("qvandtemp:", "");

    ImGui::Image((void*)(intptr_t)m_qvAndTempSlicer.getSlice()->id(), {(float)128.f, (float)128.f});
    m_pressureAndDivergenceSlicer.update(m_debugSlice);
    ImGui::LabelText("pressure and divergence:", "");

    ImGui::Image((void*)(intptr_t)m_pressureAndDivergenceSlicer.getSlice()->id(), {(float)128.f, (float)128.f});
    ImGui::End();

}

void CloudFluidSimulator::init()
{
    initFields();
}
