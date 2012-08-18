#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "BaseApplication.h"
#include "Chunk.h"
#include "Block.h"
#include "tinyXml/XmlMgr.h"

#include <fstream>
#include <string>
#include <math.h>
// 10 000 / CHWIDTH
#define MAPWIDTH  10000 / CHWIDTH

class LevelManager
{
    public:
        LevelManager(Ogre::SceneManager* sceneMgr);
        virtual ~LevelManager();

        void createWorld();
        void displayChunk(Ogre::Vector2 chunkCoord);
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        Chunk* m_Chunks[3][3];
        Block* mNonExistingBlock;

        std::ofstream flux;
        XmlMgr* mXmlManager;

        void manageVisibleFacesAt(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord);
        int realToInt(Ogre::Real num);
        std::string getId(Ogre::Vector3 coord);

        Block* getProperXBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord);
        Block* getProperYBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord);
        Block* getProperZBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord);

        void createFaceAt(std::string face, Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord);


        std::string getCubeMaterialName(int texture, std::string face);

        int getHeight(int x, int y, int seed);
        Ogre::Vector2 getNumberFromCoord(int x, int y, int seed, int pass, int max);
        int getNumber(int seed, int max, int min);
};

#endif // LEVELMANAGER_H
