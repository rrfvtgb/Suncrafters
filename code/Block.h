#ifndef BLOCK_H
#define BLOCK_H

#include "BaseApplication.h"

class Block
{
    public:
        Block();
        Block(Ogre::SceneNode* chunkNode, Ogre::Vector3 coord);
        virtual ~Block();

        std::string mTexture;
        Block* mSurroundingBlocks[6];//y-1;x+1;y+1;x-1;z+1;z-1
        Ogre::Vector3 mCoord;

        void addFace(std::string face);
    protected:
    private:

        Ogre::SceneNode* mChunkNode;
};

#endif // BLOCK_H
