#include "LevelManager.h"

#include <vector>

LevelManager::LevelManager(Ogre::SceneManager* mSceneMgr){
    this.mSceneMgr = mSceneMgr;
}

LevelManager::~LevelManager(){
    //dtor
}

LevelManager::createWorld(){
    Ogre::SceneNode* landscape = mSceneMgr->getRootSceneNode()->createChildSceneNode("landscape");
    std::vector <Chunk*> chunksList;

    for(int i = 0; i < 9; i++){
        chunksList.push(new Chunk());
    }
}
