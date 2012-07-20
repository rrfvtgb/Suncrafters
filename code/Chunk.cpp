#include "Chunk.h"

Chunk::Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord){
    this->mSceneMgr = sceneMgr;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;

    Ogre::Vector3 blockCoord;
    std::string name = Ogre::StringConverter::toString(coord.x) + ";" + Ogre::StringConverter::toString(coord.y);
    this->mChunkNode = sceneMgr->getRootSceneNode()->createChildSceneNode("chunkNode-" + name);//Convert To get LandscapeNode
    this->mChunkNode->setPosition(coord.x, 0, coord.y);

    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                blockCoord.x = this->mCoord.x + x;
                blockCoord.y = y;
                blockCoord.z = this->mCoord.y + z;
                this->m_map[x][y][z] = new Block(this->mChunkNode, blockCoord, sceneMgr);
            }
        }
    }
}
//"Virtual" Chunk for borders
Chunk::Chunk(){for(int x = 0; x < CHWIDTH; x++){for(int y = 0; y < CHHEIGHT; y++){for(int z = 0; z < CHWIDTH; z++){this->m_map[x][y][z] = new Block();}}}}

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
void Chunk::addSurroundingBlocks(){
    Block* nonExistingBlock = new Block();//When y+1 & y-1 blocks don't exists

    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                if(checkY(x, y-1, z)){
                    this->m_map[x][y][z]->mSurroundingBlocks[0] = this->m_map[x][y-1][z];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[0] = nonExistingBlock;
                }if(checkX(x+1, y, z)){
                    this->m_map[x][y][z]->mSurroundingBlocks[1] = this->m_map[x+1][y][z];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[1] = this->mSurroundingChunks[0]->m_map[0][y][z];
                }if(checkY(x, y+1, z)){
                    this->m_map[x][y][z]->mSurroundingBlocks[2] = this->m_map[x][y+1][z];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[2] = nonExistingBlock;
                }if(checkX(x-1, y, z)){
                    this->m_map[x][y][z]->mSurroundingBlocks[3] = this->m_map[x-1][y][z];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[3] = this->mSurroundingChunks[2]->m_map[CHWIDTH][y][z];
                }if(checkZ(x, y, z+1)){
                    this->m_map[x][y][z]->mSurroundingBlocks[4] = this->m_map[x][y][z+1];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[4] = this->mSurroundingChunks[3]->m_map[x][y][CHHEIGHT];
                }if(checkZ(x, y, z-1)){
                    this->m_map[x][y][z]->mSurroundingBlocks[5] = this->m_map[x][y][z-1];
                }else{
                    this->m_map[x][y][z]->mSurroundingBlocks[5] = this->mSurroundingChunks[1]->m_map[x][y][0];
                }
            }
        }
    }
    this->displayChunk();
}

void Chunk::displayChunk(){
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                this->m_map[x][y][z]->DisplayVisibleFaces();
            }
        }
    }
}
bool Chunk::checkX(int x, int y, int z){
    if(x >= CHWIDTH || x <= 0){
        return false;
    }else{
        return true;
    }

}
bool Chunk::checkZ(int x, int y, int z){
    if(z >= CHWIDTH || z < 0){
        return false;
    }else{
        return true;
    }

}
bool Chunk::checkY(int x, int y, int z){
    if(y >= CHHEIGHT || y < 0){
        return false;
    }else{
        return true;
    }
}
