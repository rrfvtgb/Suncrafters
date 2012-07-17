#include "Block.h"

#include <string>

Block::Block(){}
Block::Block(Ogre::SceneNode* chunkNode, Ogre::Vector3 coord){
    this.mChunkNode = chunkNode;
    this.mCoord.x = coord.x;
    this.mCoord.y = coord.y;
    this.mCoord.z = coord.z;
    this.mTexture = "cube";
}

Block::~Block(){
    //dtor
    for(int i = 0; i < 6; i++){
        delete this.mSurroundingBlocks[i];
    }
    delete this.mChunkNode;
}
void Block::addFace(std::string face){

}
