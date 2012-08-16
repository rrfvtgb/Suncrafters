#include "Chunk.h"

Chunk::Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord){
    this->mSceneMgr = sceneMgr;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;

    std::string name = Ogre::StringConverter::toString(coord.x) + ";" + Ogre::StringConverter::toString(coord.y);
    this->mChunkNode = sceneMgr->getRootSceneNode()->createChildSceneNode("chunkNode-" + name);//Convert To get LandscapeNode

    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                if(y == CHHEIGHT -1 && ((x == 0 || x == CHWIDTH-1) || (z == 0 || z == CHWIDTH-1))){
                    this->m_map[x][y][z] = new Block();
                    this->m_map[x][y][z]->mTexture = 0;
                }
                else{this->m_map[x][y][z] = new Block();}
            }
        }
    }
}
Chunk::Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord, std::string filename){
    this->mSceneMgr = sceneMgr;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;

    std::string name = Ogre::StringConverter::toString(coord.x) + ";" + Ogre::StringConverter::toString(coord.y);
    this->mChunkNode = sceneMgr->getSceneNode("LandscapeMgrNode")->createChildSceneNode("chunkNode-" + name);//Convert To get LandscapeNode
    this->mChunkNode->setPosition(coord.x, 0, coord.y);

    this->loadChunk(filename);
}

//"Virtual" Chunk for borders
Chunk::Chunk(){
    this->mCoord.x = -1;
    this->mCoord.y = -1;
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

void Chunk::saveChunk(){
    std::string name("bin/assets/chunks/chunk;" + Ogre::StringConverter::toString(this->mCoord.x) + ";" + Ogre::StringConverter::toString(this->mCoord.y) + ".bin");

    std::ofstream flux(name.c_str());//Create file if it doesn't exist
    flux.close();

    std::fstream myFile (name.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    int i = 0;
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                myFile.seekp(sizeof (Block) * (i));
                myFile.write((char*)&this->m_map[x][y][z], sizeof (Block));
                i++;
            }
        }
    }
    myFile.close();
}
bool Chunk::loadChunk(std::string filename){
    std::fstream myFile (filename.c_str(), std::ios::in | std::ios::out | std::ios::binary);

    if (myFile.is_open()){
        int i = 0;
        for(int x = 0; x < CHWIDTH; x++){
            for(int y = 0; y < CHHEIGHT; y++){
                for(int z = 0; z < CHWIDTH; z++){
                    myFile.seekg(sizeof (Block) * (i));
                    myFile.read((char*)&this->m_map[x][y][z], sizeof (Block));
                    i++;
                }
            }
        }
        myFile.close();
        return true;
    }else{
        return false;
    }
}
