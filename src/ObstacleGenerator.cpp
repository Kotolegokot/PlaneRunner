#include "ObstacleGenerator.h"

using namespace irr;

ObstacleGenerator::ObstacleGenerator(IrrlichtDevice *device, f32 farValue, f32 buffer) :
    device(device), farValue(farValue), buffer(buffer) {}

void ObstacleGenerator::generate(const core::vector3df &playerPosition)
{
    // The Z loop must be the first here, because the "nodes" deque must be sorted by nodes' Z coordinate
    for (f32 z = preciseEdge(playerPosition.Z); z < preciseEdge(playerPosition.Z + farValueWithBuffer()); z += STEP)
        for (f32 x = preciseEdge(playerPosition.X - farValueWithBuffer()); x < preciseEdge(playerPosition.X + farValueWithBuffer()); x += STEP)
            for (f32 y = preciseEdge(playerPosition.Y - farValueWithBuffer()); y < preciseEdge(playerPosition.Y + farValueWithBuffer()); y += STEP) {
                bool insideX = false, insideY = false, insideZ = false;
                insideX = x > generatedEdgeLeft && x < generatedEdgeRight;
                insideY = y > generatedEdgeBottom && y < generatedEdgeTop;
                insideZ = z < generatedEdgeZ;
                if (!(insideX && insideY && insideZ)) {
                    scene::ISceneManager *sceneManager = device->getSceneManager();
                    scene::ISceneNode *node = sceneManager->addCubeSceneNode(50.f, 0, -1, core::vector3df(x, y, z));
                    node->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/textures/lsd.png"));

                    nodes.push_back(node);
                    cubeCount++;
                }
            }

    generatedEdgeLeft = preciseEdge(playerPosition.X - farValueWithBuffer());
    generatedEdgeRight = preciseEdge(playerPosition.X + farValueWithBuffer());
    generatedEdgeBottom = preciseEdge(playerPosition.Y - farValueWithBuffer());
    generatedEdgeTop = preciseEdge(playerPosition.Y + farValueWithBuffer());
    generatedEdgeZ = preciseEdge(playerPosition.Z + farValueWithBuffer());

    removeLeftBehind(playerPosition.Z);
}

f32 ObstacleGenerator::preciseEdge(f32 edge) const
{
    return edge - (edge - floor(edge / STEP)*STEP);
}

void ObstacleGenerator::removeLeftBehind(f32 playerZ)
{
    while (!nodes.empty())
        if (nodes.front()->getPosition().Z < playerZ) {
            nodes.front()->remove();
            nodes.pop_front();
            cubeCount--;
        } else {
            break;
        }
}

u32 ObstacleGenerator::getCubeCount() const
{
    return cubeCount;
}

f32 ObstacleGenerator::farValueWithBuffer() const
{
    return farValue + buffer;
}

void ObstacleGenerator::setFarValue(f32 value)
{
    farValue = value;
}

f32 ObstacleGenerator::getFarValue() const
{
    return farValue;
}

void ObstacleGenerator::setBuffer(f32 buffer)
{
    this->buffer = buffer;
}

f32 ObstacleGenerator::getBuffer() const
{
    return buffer;
}