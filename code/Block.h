#ifndef BLOCK_H
#define BLOCK_H

#include "BaseApplication.h"

class Block
{
    public:
        Block();
        virtual ~Block();

        int mTexture;
        Ogre::Vector3 mCoord;

        bool isVisible();
        //void addFace(int face, Ogre::SceneNode* blockNode);
    protected:
    private:
};

#endif // BLOCK_H
