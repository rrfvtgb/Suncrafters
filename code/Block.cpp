#include "Block.h"

#include <string>

Block::Block(Ogre::SceneManager mSceneMgr, Ogre::Vector3 coord){
    this.mSceneMgr = mSceneMgr;
    this.mCoord.x = coord.x;
    this.mCoord.y = coord.y;
    this.mCoord.z = coord.z;
    this.mTexture = "cube";
}

Block::~Block(){
    //dtor
}
Block::addFace(std::string face){

}
