#include "Block.h"

#include <string>
#include <iostream>
#include <fstream>

Block::Block(){this->mTexture = "";}
Block::Block(Ogre::SceneNode* chunkNode, Ogre::Vector3 coord, Ogre::SceneManager* sceneMgr){
    this->mChunkNode = chunkNode;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;
    this->mCoord.z = coord.z;
    this->mTexture = "cube";
    this->mSceneMgr = sceneMgr;

}


Block::~Block(){
    //dtor
    for(int i = 0; i < 6; i++){
        delete this->mSurroundingBlocks[i];
    }
    delete this->mChunkNode;
}
void Block::addFace(int face, Ogre::SceneNode* blockNode){
    std::string str = "face:" + Ogre::StringConverter::toString(face) + "-"
                          + Ogre::StringConverter::toString(this->mCoord.x)
                    + ";" + Ogre::StringConverter::toString(this->mCoord.y)
                    + ";" + Ogre::StringConverter::toString(this->mCoord.z);

    Ogre::SceneNode* faceNode = blockNode->createChildSceneNode("faceNode-" + str);
    Ogre::Entity* faceEnt = mSceneMgr->createEntity("face-" + str, "blockMesh");
    faceEnt->setMaterialName("cube_metal");

    faceNode->attachObject(faceEnt);

    switch(face){ // Translate after settingPosition <- important
        case 0 : faceNode->pitch(Ogre::Degree(90));break;
        case 1 :
            faceNode->yaw(Ogre::Degree(90));
            faceNode->setPosition(this->mCoord.x, this->mCoord.y, this->mCoord.z);
            faceNode->translate(40,0,-40 + 80);
        break;
        case 2 :
            faceNode->roll(Ogre::Degree(180));
            faceNode->pitch(Ogre::Degree(90));
            faceNode->setPosition(this->mCoord.x, this->mCoord.y, this->mCoord.z);
            faceNode->translate(0, 80, 0);
        break;
        case 3 :
            faceNode->yaw(Ogre::Degree(-90));
            faceNode->setPosition(this->mCoord.x, this->mCoord.y, this->mCoord.z);
            faceNode->translate(-40,0,-40 + 80);
        break;
        case 4 : faceNode->setPosition(this->mCoord.x, this->mCoord.y, this->mCoord.z+80);break;
        case 5 :
            faceNode->yaw(Ogre::Degree(180));
            faceNode->setPosition(this->mCoord.x, this->mCoord.y, this->mCoord.z);
        break;
    }
    faceNode->scale(0.8, 0.8, 0.8);
}
void Block::DisplayVisibleFaces(){
    std::string const nomFichier("report.txt");
    std::ofstream flux(nomFichier.c_str());

    std::string str = "blockNode-" + Ogre::StringConverter::toString(this->mCoord.x)
                    + ";" + Ogre::StringConverter::toString(this->mCoord.y)
                    + ";" + Ogre::StringConverter::toString(this->mCoord.z);
    Ogre::SceneNode* blockNode = this->mChunkNode->createChildSceneNode(str);
    flux << str << std::endl;
    for(int i = 0; i < 6; i++){
        flux << "At i = " << i << std::endl;
        flux << "At i = " << i << " texture =" << this->mSurroundingBlocks[i]->mTexture << std::endl;
        if(isVisible(this->mSurroundingBlocks[i])){
            flux << "At i = " << i << " texture =" << isVisible(this->mSurroundingBlocks[i]) << std::endl;
            addFace(i, blockNode);
        }
        flux << "did not bug" << std::endl;
    }
    if(blockNode->numChildren() == 0){
        this->mChunkNode->removeAndDestroyChild(str);
    }
}
bool Block::isVisible(Block* surroundingBlock){
    return (surroundingBlock->mTexture == "") ? true : false;
}
