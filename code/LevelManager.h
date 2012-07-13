#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "BaseApplication.h"

class LevelManager
{
    public:
        LevelManager(Ogre::SceneManager* mSceneMgr, int worldId);
        virtual ~LevelManager();

        void createWorld();
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
};

#endif // LEVELMANAGER_H
