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
            }
        }
    }
}
Chunk::Chunk(Ogre::SceneManager* sceneMgr, Ogre::Vector2 coord, std::string filename){
    this->mSceneMgr = sceneMgr;
    this->mCoord.x = coord.x;
    this->mCoord.y = coord.y;

    std::string name = Ogre::StringConverter::toString(coord.x) + ";" + Ogre::StringConverter::toString(coord.y);
    this->mChunkNode = sceneMgr->getRootSceneNode()->createChildSceneNode("chunkNode-" + name);//Convert To get LandscapeNode
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
    std::string name("bin/assets/chunks/chunk" + Ogre::StringConverter::parseInt(coord.x) + ";" + Ogre::StringConverter::parseInt(coord.y) + ".bin");

    std::ofstream flux(name.c_str());//Create file if it doesn't exist
    flux.close();

    fstream myFile (name.c_str(), ios::in | ios::out | ios::binary);

    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                myFile.seekp(sizeof (Block) * (x+y+z));
                myFile.write((char*)&this->m_map[x][y][z], sizeof (Block));
            }
        }
    }
    myFile.close();
}
bool Chunk::loadChunk(std::string filename){
    fstream file ("example.bin", ios::in|ios::binary|ios::ate);
    if (file.is_open()){
        for(int x = 0; x < CHWIDTH; x++){
            for(int y = 0; y < CHHEIGHT; y++){
                for(int z = 0; z < CHWIDTH; z++){
                    myFile.seekg(sizeof (Block) * (x+y+z));
                    myFile.read((char*)&this->m_map[x][y][z], sizeof (Block));
                }
            }
        }
    }else{
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, std::string("Error While Loading Chunks. File is :" + filename), "An exception has occured!", MB_OK | MB_ICONERROR| MB_TASKMODAL);
        #else
            std::cerr << "An exception has occured: " << std::string("Error While Loading Chunks. File is :" + filename) << std::endl;
        #endif
    }
}
