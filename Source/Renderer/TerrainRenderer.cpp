#include "TerrainRenderer.h"

#include "../GLLib/GLFunctions.h"
#include "../Maths/Matrix.h"
#include "../Camera.h"
#include "../Terrain/Terrain.h"

#include <iostream>

TerrainRenderer::TerrainRenderer()
:   m_terrainShader ("terrain", "primitive")
,   m_floorTexture  ("floor")
{
    m_locModelMatrix    = m_terrainShader.getUniformLocation("modelMatrix");
    m_locProjViewMatrix = m_terrainShader.getUniformLocation("projectionViewMatrix");
}

void TerrainRenderer::add(const Terrain& terrain)
{
    m_terrains.push_back(&terrain);
}

void TerrainRenderer::render(const Camera& camera)
{
    m_floorTexture.bind();
    m_terrainShader.useProgram();

    GL::loadUniform(m_locProjViewMatrix, camera.getProjViewMatrix());

    for (auto& terrain : m_terrains)
    {
        terrain->getModel().bindVAO();
        GL::loadUniform(m_locModelMatrix, createModelMatrix(terrain->getPosition(), {0, 0, 0}));
        GL::drawElements(terrain->getModel().getIndicesCount());
    }
    m_terrains.clear();
}