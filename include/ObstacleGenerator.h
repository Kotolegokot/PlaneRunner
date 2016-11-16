/* This file is part of PlaneRunner.
 *
 * PlaneRunner is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PlaneRunner is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PlaneRunner. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OBSTACLEGENERATOR_H
#define OBSTACLEGENERATOR_H

#include <list>
#include <memory>
#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include "options.h"
#include "MotionState.h"
#include "IObstacle.h"
#include "IBody.h"
#include "Randomizer.h"
#include "ObstaclePatternFactory.h"
#include "Chunk.h"
#include "obstacles/Box.h"
#include "obstacles/Tetrahedron.h"
#include "obstacles/Icosahedron.h"
#include "obstacles/Icosphere2.h"
#include "obstacles/Cone.h"
#include "patterns/Crystal.h"
#include "patterns/Tunnel.h"
#include "patterns/Valley.h"

using namespace irr;

constexpr std::size_t CHUNK_SIZE = 8;
using ChunkDB = std::array<Chunk<CHUNK_SIZE>, 10000>;

// this class is responsible for generating obstacles on the fly
class ObstacleGenerator
{
public:
    ObstacleGenerator(IrrlichtDevice &device, btDynamicsWorld &world, btScalar farValue = 1500, btScalar buffer = 300);
    void generate(const core::vector3df &playerPosition, const ChunkDB &chunkDB);
    u32 getCubeCount() const;

    void setFarValue(btScalar value);
    btScalar getFarValue() const;
    void setBuffer(btScalar buffer);
    btScalar getBuffer() const;

private:
    static constexpr btScalar CELL_SIZE = 250;
    static constexpr btScalar CHUNK_LENGTH = CHUNK_SIZE * CELL_SIZE;

    void stickToGrid(const core::vector3df &playerPosition, long &edgeLeft, long &edgeRight,
                     long &edgeBottom, long &edgeTop, long &edgeBack, long &edgeFront) const;
    unsigned long generateChunk(long x, long y, long z, const ChunkDB &chunkDB);
    void removeLeftBehind(btScalar playerZ);
    btScalar farValueWithBuffer() const;

    IrrlichtDevice &device;
    std::list<std::unique_ptr<IObstacle>> obstacles;

    u32 obstacleCount = 0;

    btScalar farValue = 0;
    // buffer is used to generate obstacles a bit farther than
    //      the camera's far value so that player sees them
    //      smoothly floating into the view range
    btScalar buffer = 0;

    long generatedEdgeFront = 1;
    long generatedEdgeLeft = 0;
    long generatedEdgeRight = 0;
    long generatedEdgeTop = 0;
    long generatedEdgeBottom = 0;

    btDynamicsWorld &world; // physics world
};

#endif // OBSTACLEGENERATOR_H
