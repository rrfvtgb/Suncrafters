#include "Chunk.h"

Chunk::Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord){
    this->mSceneMgr = sceneMgr;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;

    std::string name = Ogre::StringConverter::toString(coord.x) + ";" + Ogre::StringConverter::toString(coord.y);
    this->mChunkNode = sceneMgr->getRootSceneNode()->createChildSceneNode("chunkNode-" + name);//Convert To get LandscapeNode
    this->mChunkNode->setPosition(coord.x, 0, coord.y);

    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                this->m_map[x][y][z] = new Block();
                this->m_map[x][y][z]->mTexture = 1;
            }
        }
    }
}
//"Virtual" Chunk for borders
Chunk::Chunk(){
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                this->m_map[x][y][z] = new Block();
            }
        }
    }
}

Chunk::~Chunk(){
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                delete this->m_map[x][y][z];
            }
        }
    }
    delete this->mChunkNode;
    delete this->mSceneMgr;
}

