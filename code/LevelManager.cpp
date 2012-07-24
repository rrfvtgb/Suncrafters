#include "LevelManager.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

LevelManager::LevelManager(Ogre::SceneManager* sceneMgr) /*: flux(std::string("report.txt").c_str())*/{
    this->mSceneMgr = sceneMgr;
    this->mNonExistingBlock = new Block();
}

LevelManager::~LevelManager(){
    for(int x = 0;x<3;x++){
        for(int y = 0; y < 3; y++){
            delete m_Chunks[x][y];
        }
    }
    delete this->mSceneMgr;
    delete this->mNonExistingBlock;
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

    for(int x = 0;x<3;x++){
        for(int y = 0; y < 3; y++){
            this->displayChunk(x, y);
        }
    }
}
void LevelManager::displayChunk(int x1, int y1){
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                this->isBlockVisibleAt(x1, y1, x, y, z);
            }
        }
    }
}
Block* LevelManager::getProperXBlock(int x1, int y1, int x, int y, int z){
    if(x > CHWIDTH-1){
        if(x1 == 2){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[x1+1][y1]->m_map[0][y][z];
        }
    }else if(x < 0){
        if(x1 == 0){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[x1-1][y1]->m_map[CHWIDTH-1][y][z];
        }
    }else{
        return this->m_Chunks[x1][y1]->m_map[x][y][z];
    }
}
Block* LevelManager::getProperYBlock(int x1, int y1, int x, int y, int z){
    if(y > CHHEIGHT-1 || y < 0){
        return this->mNonExistingBlock;
    }else{
        return this->m_Chunks[x1][y1]->m_map[x][y][z];
    }
}
Block* LevelManager::getProperZBlock(int x1, int y1, int x, int y, int z){
    if(z > CHWIDTH-1){
        if(y1 == 2){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[x1][y1+1]->m_map[x][y][0];
        }
    }else if(z < 0){
        if(y1 == 0){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[x1][y1-1]->m_map[x][y][CHWIDTH-1];
        }
    }else{
        return this->m_Chunks[x1][y1]->m_map[x][y][z];
    }
}
void LevelManager::isBlockVisibleAt(int x1, int y1, int x, int y, int z){

    if(!this->m_Chunks[x1][y1]->m_map[x][y][z]->isVisible()){
        if(this->getProperXBlock(x1, y1, x+1, y, z)->mTexture == 0){
            this->createFaceAt("x+1", x1, y1, x, y, z);
        }
        if(this->getProperXBlock(x1, y1, x-1, y, z)->mTexture == 0){
            this->createFaceAt("x-1", x1, y1, x, y, z);
        }
        if(this->getProperYBlock(x1, y1, x, y+1, z)->mTexture == 0){
            this->createFaceAt("y+1", x1, y1, x, y, z);
        }
        if(this->getProperYBlock(x1, y1, x, y-1, z)->mTexture == 0){
            this->createFaceAt("y-1", x1, y1, x, y, z);
        }
        if(this->getProperZBlock(x1, y1, x, y, z+1)->mTexture == 0){
            this->createFaceAt("z+1", x1, y1, x, y, z);
        }
        if(this->getProperZBlock(x1, y1, x, y, z-1)->mTexture == 0){
            this->createFaceAt("z-1", x1, y1, x, y, z);
        }
    }
}
void LevelManager::createFaceAt(std::string face, int x1, int y1, int x, int y, int z){

    //this->flux << x << ";" << y << ";" << z << "& face = " << face << std::endl;

    x = (this->m_Chunks[x1][y1]->mCoord.x + x)*80;
    y = y * 80;
    z = (this->m_Chunks[x1][y1]->mCoord.y + z)*80;

    std::string id = Ogre::StringConverter::toString(x) + ";" +
         Ogre::StringConverter::toString(y) + ";" +
         Ogre::StringConverter::toString(z); //sceneNode id and entity Id
    /*if(mSceneMgr->hasSceneNode("faceNode;" + face + ";" +id)){
        return;
    }*/
    //this->flux << id << "& face = " << face << std::endl << std::endl;

    Ogre::Entity *faceEnt = mSceneMgr->createEntity("face;" + face + ";" +id, "blockMesh");

    Ogre::SceneNode* cubeNode;
    if(mSceneMgr->hasSceneNode("cubeNode;" + id)){//If block node already exists get it
        cubeNode = mSceneMgr->getSceneNode("cubeNode;" + id);
    }else{//Else create it
        cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("cubeNode;" + id);
    }
    Ogre::SceneNode* faceNode = cubeNode->createChildSceneNode("faceNode;" + face + ";" +id);
    faceNode->attachObject(faceEnt);


    if(face.compare("x+1") == 0){
        faceNode->yaw(Ogre::Degree(90));
        faceNode->setPosition(x, y, z);
        faceNode->translate(40,0,-40 + 80);
    }else if(face.compare("x-1") == 0){
        faceNode->yaw(Ogre::Degree(-90));
        faceNode->setPosition(x, y, z);
        faceNode->translate(-40,0,-40 + 80);
    }else if(face.compare("y+1") == 0){
        faceNode->roll(Ogre::Degree(180));
        faceNode->pitch(Ogre::Degree(90));
        faceNode->setPosition(x, y, z);
        faceNode->translate(0, 80, 0);
    }else if(face.compare("y-1") == 0){
        faceNode->pitch(Ogre::Degree(90));
        faceNode->setPosition(x, y, z);
    }else if(face.compare("z-1") == 0){
        faceNode->yaw(Ogre::Degree(180));
        faceNode->setPosition(x, y, z);
    }else{
        faceNode->setPosition(x, y, z+80);
    }
    faceNode->scale(0.8, 0.8, 0.8);
}
