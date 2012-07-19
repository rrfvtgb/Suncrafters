#ifndef BLOCK_H
#define BLOCK_H

#include "BaseApplication.h"

class Block
{
    public:
        Block();
        Block(Ogre::SceneNode* chunkNode, Ogre::Vector3 coord, Ogre::SceneManager* sceneMgr);
        virtual ~Block();

        std::string mTexture;
        Block* mSurroundingBlocks[6];//y-1;x+1;y+1;x-1;z+1;z-1
        Ogre::Vector3 mCoord;

        void DisplayVisibleFaces();
        bool isVisible(Block* surroundingBlock);
        void addFace(int face, Ogre::SceneNode* blockNode);
    protected:
    private:

        Ogre::SceneNode* mChunkNode;
        Ogre::SceneManager* mSceneMgr;
};

#endif // BLOCK_H
