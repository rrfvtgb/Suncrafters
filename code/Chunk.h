#ifndef CHUNK_H
#define CHUNK_H

#include "BaseApplication.h"
#include "Block.h"

#define CHWIDTH 20
#define CHHEIGHT 32

class Chunk
{
    public:
        Chunk();
        Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord);
        virtual ~Chunk();

        Block* m_map[CHWIDTH][CHHEIGHT][CHWIDTH];
        Ogre::Vector2 mCoord;
        Chunk* mSurroundingChunks[4];//x+1;y-1;x-1;y+1 //see schemes file
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        Ogre::SceneNode* mChunkNode;

};

#endif // CHUNK_H
