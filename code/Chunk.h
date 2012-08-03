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
        Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord, std::string filename);
        virtual ~Chunk();
        void saveChunk();
        bool loadChunk(std::string filename);

        Block* m_map[CHWIDTH][CHHEIGHT][CHWIDTH];
        Ogre::Vector2 mCoord;
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        Ogre::SceneNode* mChunkNode;

};

#endif // CHUNK_H
