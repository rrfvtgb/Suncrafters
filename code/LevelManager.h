#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "BaseApplication.h"
#include "Chunk.h"
#include "Block.h"
#include "tinyXml/tinyxml.h"
#include <fstream>

class LevelManager
{
    public:
        LevelManager(Ogre::SceneManager* sceneMgr);
        virtual ~LevelManager();

        void createWorld();
        void displayChunk(int x, int y);
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        Chunk* m_Chunks[3][3];
        Block* mNonExistingBlock;

        std::ofstream flux;
        TiXmlHandle* mHdl;

        Block* getProperXBlock(int x1, int y1, int x, int y, int z);
        Block* getProperYBlock(int x1, int y1, int x, int y, int z);
        Block* getProperZBlock(int x1, int y1, int x, int y, int z);

        void manageVisibleFacesAt(int x1, int y1, int x, int y, int z);
        void createFaceAt(std::string face, int x1, int y1, int x, int y, int z);

        std::string getCubeMaterialName(int texture, std::string face);
};

#endif // LEVELMANAGER_H
