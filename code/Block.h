#ifndef BLOCK_H
#define BLOCK_H

#include "BaseApplication.h"

class Block
{
    public:
        Block(Ogre::SceneManager mSceneMgr, Ogre::Vector3 coord);
        virtual ~Block();

        std::string mTexture;
        Block[6] mSurroundingBlocks;
        Ogre::Vector3 mCoord;

        void addFace(std::string face);
    protected:
    private:

        Ogre::SceneManager mSceneMgr;
};

#endif // BLOCK_H
