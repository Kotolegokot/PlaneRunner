#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H

#include "ObjMesh.h"
#include "IBody.h"

using namespace irr;

#define MASS_COEFFICIENT 0.000002
#define ICOSAHEDRON_MODEL "media/models/icosahedron.obj"

class Icosahedron : public IBody
{
public:
    Icosahedron(btDynamicsWorld *world, IrrlichtDevice *device, const btVector3 &position, f32 radius) :
        IBody(world), device(device), position(position), radius(radius)
    {
        createBody();
    }

    virtual ~Icosahedron()
    {
        // so that commonShape is not deleted thousand times within IBody::~IBody
        shape = nullptr;
    }

    virtual btScalar getMass()
    {
        return radius*radius*radius*MASS_COEFFICIENT;
    }

protected:
    virtual void createNode()
    {
        mesh = device->getSceneManager()->getMesh(ICOSAHEDRON_MODEL);
        node = device->getSceneManager()->addMeshSceneNode(mesh);
        node->setScale(core::vector3df(200, 200, 200));
        node->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/textures/lsd.png"));

        node->setMaterialFlag(video::EMF_FOG_ENABLE, true);
        node->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER, true);
        node->setMaterialFlag(video::EMF_TRILINEAR_FILTER, true);
        node->setMaterialFlag(video::EMF_ANTI_ALIASING, true);
    }

    virtual void createMotionState()
    {
        motionState = new MotionState(btTransform(btQuaternion(0, 0, 0, 1), position), node);
    }

    virtual void createShape()
    {
        if (!commonShape) {
            ObjMesh objMesh(ICOSAHEDRON_MODEL);

            commonShape = new btConvexHullShape();
            objMesh.setPoints(commonShape);
            commonShape->setLocalScaling(btVector3(200, 200 ,200));
        }

        shape = commonShape;
    }


private:
    IrrlichtDevice *device = nullptr;
    scene::IMesh *mesh = nullptr;
    btVector3 position;
    f32 radius;

    static btConvexHullShape *commonShape;
};

#endif // ICOSAHEDRON_H
