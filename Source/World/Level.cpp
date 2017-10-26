#include "Level.h"

#include "../Util/Random.h"
#include "../Model/ModelLoader.h"
#include "../Renderer/MasterRenderer.h"

#include <iostream>

namespace
{
    unsigned toHex (sf::Color colour)
    {
        return (colour.r << 16) | (colour.g << 8) | colour.b;
    }

    //Tree = 0x7F3300;
}

Level::Level(const std::string& name)
:   m_terrain       ({-100, 0, -100})
{
    m_levelImage.loadFromFile("res/levels/" + name + ".png");
    m_mapSizeZ = m_levelImage.getSize().y;
    m_mapSizeX = m_levelImage.getSize().x;

    loadLevel();
}

void Level::render(MasterRenderer& renderer) const
{
    renderer.addObject(m_terrain);

    for (auto& entity : m_entities)
        renderer.addObject(entity);
}

const std::vector<Entity>& Level::getEntities() const
{
    return m_entities;
}

void Level::loadLevel()
{
    Random<> randomisor;

    std::vector<glm::vec3> treePositions;
    for (unsigned z = 0; z < m_mapSizeZ; z++)
    for (unsigned x = 0; x < m_mapSizeX; x++)
    {
        glm::vec3 adjPos(x * SCALE, -1, z * SCALE);
        unsigned colourHex = toHex(m_levelImage.getPixel(x, z));
        if (colourHex == 0x7F3300)
        {
            glm::vec3 position(adjPos.x + randomisor.getFloatInRange(-0.5, 0.5),
                                -1,
                                adjPos.z + randomisor.getFloatInRange(-0.5, 0.5));

            treePositions.emplace_back(position);
        }
        //more models...
    }

    m_treeModel.create("tree1", "bark");

    for (auto& pos : treePositions)
    {
        m_entities.emplace_back(m_treeModel, pos);
    }
}



















