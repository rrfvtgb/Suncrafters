#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "BaseApplication.h"
#include "Chunk.h"

class LevelManager
{
    public:
        LevelManager(Ogre::SceneManager* sceneMgr);
        virtual ~LevelManager();

        void createWorld();
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        Chunk* m_Chunks[3][3];
};

#endif // LEVELMANAGER_H
