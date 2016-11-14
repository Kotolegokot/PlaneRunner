#ifndef OBSTACLEPATTERNFACTORY_H
#define OBSTACLEPATTERNFACTORY_H

#include <memory>
#include "IObstaclePattern.h"
#include "patterns/Crystal.h"
#include "patterns/Tunnel.h"
#include "patterns/Valley.h"

class ObstaclePatternFactory {
    ObstaclePatternFactory(btDynamicsWorld &world, IrrlichtDevice &device, btScalar cellSize) :
        IObstaclePattern(world, device, cellSize)
    {
        patterns[0] = std::make_unique<Crystal>(world, device, cellSize);
        patterns[1] = std::make_unique<Tunnel>(world, device, cellSize);
        patterns[2] = std::make_unique<Valley>(world, device, cellSize);
    }

    IObstaclePattern &operator [](std::size_t index)
    {
        return *patterns[index];
    }

    const IObstaclePattern &operator [](std::size_t index) const
    {
        return *patterns[index];
    }

    std::size_t size() const
    {
        return patterns.size();
    }

private:
    std::array<std::unique_ptr<IObstaclePattern>, 3> patterns;
};

#endif // OBSTACLEPATTERNFACTORY_H
