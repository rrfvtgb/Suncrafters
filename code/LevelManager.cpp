#include "LevelManager.h"

#include <vector>

LevelManager::LevelManager(Ogre::SceneManager* sceneMgr){
    this->mSceneMgr = sceneMgr;
}

LevelManager::~LevelManager(){
    for(int x = 0;x<3;x++){
        for(int y = 0; y < 3; y++){
            delete m_Chunks[x][y];
        }
    }
    delete this->mSceneMgr;
}

void LevelManager::createWorld(){
    Ogre::SceneNode* landscape = mSceneMgr->getRootSceneNode()->createChildSceneNode("landscape");
    Ogre::Vector2 chunkCoord;

    for(int x = 0; x < 3; x++){//instantiation of chunks
        for(int y = 0; y < 3; y++){
            chunkCoord.x = CHWIDTH * x;
            chunkCoord.y = CHWIDTH * y;
            this->m_Chunks[x][y] = new Chunk(this->mSceneMgr, chunkCoord);
        }
    }
    Chunk *ch = new Chunk();
    for(int x = 0;x<3;x++){//surrounding chunks
        for(int y = 0; y < 3; y++){
            if(x+1 < 3){
                this->m_Chunks[x][y]->mSurroundingChunks[0] = m_Chunks[x+1][y];
            }else{
                this->m_Chunks[x][y]->mSurroundingChunks[0] = ch;
            }if(y-1 >= 0){
                this->m_Chunks[x][y]->mSurroundingChunks[1] = m_Chunks[x][y-1];
            }else{
                this->m_Chunks[x][y]->mSurroundingChunks[1] = ch;
            }if(x-1 >= 0){
                this->m_Chunks[x][y]->mSurroundingChunks[2] = m_Chunks[x-1][y];
            }else{
                this->m_Chunks[x][y]->mSurroundingChunks[2] = ch;
            }if(y+1 < 3){
                this->m_Chunks[x][y]->mSurroundingChunks[3] = m_Chunks[x][y+1];
            }else{
                this->m_Chunks[x][y]->mSurroundingChunks[3] = ch;
            }
        }
    }
    for(int x = 0;x<3;x++){//surrounding blocks
        for(int y = 0; y < 3; y++){
            this->m_Chunks[x][y]->addSurroundingBlocks();
        }
    }

}
