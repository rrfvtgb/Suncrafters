#include "Chunk.h"

Chunk::Chunk(Ogre::SceneManager mSceneMgr, Ogre::Vector2 coord){
    this.mSceneMgr = mSceneMgr;
    this.mCoord.x = coord.x;
    this.mCoord.y = coord.y;

    Ogre::Vector3 blockCoord;
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                blockCoord.x = this.mCoord.x + x;
                blockCoord.y = y;
                blockCoord.z = this.mCoord.y + z;
                m_map[x][y][z] = new Block(mSceneMgr, blockCoord);
            }
        }
    }
}

Chunk::~Chunk(){
    //dtor
}
