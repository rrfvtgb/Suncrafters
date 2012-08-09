#include "LevelManager.h"
#include "PathMgr.h"

#include <vector>
#include <iostream>

LevelManager::LevelManager(Ogre::SceneManager* sceneMgr) : flux(std::string("report.txt").c_str()){
    this->mSceneMgr = sceneMgr;
    this->mNonExistingBlock = new Block();
    this->mNonExistingBlock->mTexture = 0;

    mXmlManager = new XmlMgr();
    mXmlManager->loadFile(std::string(PathMgr::getDataStorageFolder() + "textures/textures.xml"));
}

void LevelManager::createWorld(){
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
            this->displayChunk(Ogre::Vector2(x, y));
        }
    }
}
void LevelManager::displayChunk(Ogre::Vector2 chunkCoord){
    for(int x = 0; x < CHWIDTH; x++){
        for(int y = 0; y < CHHEIGHT; y++){
            for(int z = 0; z < CHWIDTH; z++){
                this->manageVisibleFacesAt(chunkCoord, Ogre::Vector3(x, y, z));
            }
        }
    }
}
/* if Block isNotAir
 * check surrounding if block are air
 * and add face when is air
 */
void LevelManager::manageVisibleFacesAt(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord){

    if(this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)]->isNotAir()){
        cubeCoord.x++;
        if(this->getProperXBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.x--;this->createFaceAt("x+1", chunkCoord, cubeCoord);}else{cubeCoord.x--;}
        cubeCoord.x--;
        if(this->getProperXBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.x++;this->createFaceAt("x-1", chunkCoord, cubeCoord);}else{cubeCoord.x++;}
        cubeCoord.y++;
        if(this->getProperYBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.y--;this->createFaceAt("y+1", chunkCoord, cubeCoord);}else{cubeCoord.y--;}
        cubeCoord.y--;
        if(this->getProperYBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.y++;this->createFaceAt("y-1", chunkCoord, cubeCoord);}else{cubeCoord.y++;}
        cubeCoord.z++;
        if(this->getProperZBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.z--;this->createFaceAt("z+1", chunkCoord, cubeCoord);}else{cubeCoord.z--;}
        cubeCoord.z--;
        if(this->getProperZBlock(chunkCoord, cubeCoord)->mTexture == 0){cubeCoord.z++;this->createFaceAt("z-1", chunkCoord, cubeCoord);}
        //no need to add 1 since it is not a pointer
    }
}

int LevelManager::realToInt(Ogre::Real num){
    return (int) num;
}

Block* LevelManager::getProperXBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord){
    if(cubeCoord.x > CHWIDTH-1){
        if(chunkCoord.x == 2){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[realToInt(chunkCoord.x)+1][realToInt(chunkCoord.y)]->m_map[0][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)];
        }
    }else if(cubeCoord.x < 0){
        if(chunkCoord.x == 0){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[realToInt(chunkCoord.x)-1][realToInt(chunkCoord.y)]->m_map[CHWIDTH-1][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)];
        }
    }else{
            return this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)];
    }
}

Block* LevelManager::getProperYBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord){
    if(cubeCoord.y > CHHEIGHT-1 || cubeCoord.y < 0){
        return this->mNonExistingBlock;
    }else{
        return this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)];
    }
}

Block* LevelManager::getProperZBlock(Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord){
    if(cubeCoord.z > CHWIDTH-1){
        if(chunkCoord.y == 2){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)+1]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][0];
        }
    }else if(cubeCoord.z < 0){
        if(chunkCoord.y == 0){
            return this->mNonExistingBlock;
        }else{
            return this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)-1]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][CHWIDTH-1];
        }
    }else{
        return this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)];
    }
}

void LevelManager::createFaceAt(std::string face, Ogre::Vector2 chunkCoord, Ogre::Vector3 cubeCoord){
    flux << "Chunk : " << chunkCoord << std::endl;
    flux << "cube : " << cubeCoord << std::endl;
    int texBlock = this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->m_map[realToInt(cubeCoord.x)][realToInt(cubeCoord.y)][realToInt(cubeCoord.z)]->mTexture;//needed before x,y,z coord changes

    cubeCoord.x = (this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->mCoord.x + cubeCoord.x)*80;
    cubeCoord.y = cubeCoord.y * 80;
    cubeCoord.z = (this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->mCoord.y + cubeCoord.z)*80;

    std::string id = this->getId(cubeCoord);//sceneNode id and entity Id
    Ogre::Entity *faceEnt = mSceneMgr->createEntity("face;" + face + ";" +id, "blockMesh");

    Ogre::SceneNode* cubeNode;
    if(mSceneMgr->hasSceneNode("cubeNode;" + id)){//If block node already exists get it
        cubeNode = mSceneMgr->getSceneNode("cubeNode;" + id);
    }else{//Else create it
        cubeNode = this->m_Chunks[realToInt(chunkCoord.x)][realToInt(chunkCoord.y)]->mChunkNode->createChildSceneNode("cubeNode;" + id);
    }

    Ogre::SceneNode* faceNode = cubeNode->createChildSceneNode("faceNode;" + face + ";" +id);
    faceNode->attachObject(faceEnt);

    if(face.compare("x+1") == 0){
        faceNode->yaw(Ogre::Degree(90));
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z);
        faceNode->translate(40,0,-40 + 80);
    }else if(face.compare("x-1") == 0){
        faceNode->yaw(Ogre::Degree(-90));
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z);
        faceNode->translate(-40,0,-40 + 80);
    }else if(face.compare("y+1") == 0){
        faceNode->roll(Ogre::Degree(180));
        faceNode->pitch(Ogre::Degree(90));
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z);
        faceNode->translate(0, 80, 0);
    }else if(face.compare("y-1") == 0){
        faceNode->pitch(Ogre::Degree(90));
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z);
    }else if(face.compare("z-1") == 0){
        faceNode->yaw(Ogre::Degree(180));
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z);
    }else{
        faceNode->setPosition(cubeCoord.x, cubeCoord.y, cubeCoord.z+80);
    }
    faceNode->scale(0.8, 0.8, 0.8);
    faceEnt->setMaterialName(this->getCubeMaterialName(texBlock, face).c_str());
}
std::string LevelManager::getId(Ogre::Vector3 coord){
    return  Ogre::StringConverter::toString(coord.x) + ";" +
            Ogre::StringConverter::toString(coord.y) + ";" +
            Ogre::StringConverter::toString(coord.z);
}
std::string LevelManager::getCubeMaterialName(int texture, std::string face){
    std::string cubeFace;
    if(face.compare("y+1") == 0){cubeFace = "top";}
    else if(face.compare("y-1") == 0){cubeFace = "bottom";}
    else{cubeFace = "side";}

    TiXmlElement* element = mXmlManager->getDocumentFirstChildElement();
    TiXmlElement* sides(0);

    if(!element){
		this->flux << "No root node or root node haven't got any child nodes" << std::endl;
		return std::string("Default");
    }

	while (element){
		if(Ogre::StringConverter::parseInt(element->Attribute("id")) == texture){
            sides = element->FirstChildElement();
            while(sides){
                if(sides->Value() == cubeFace){
                    return sides->GetText();
                    break;
                }
                sides = sides->NextSiblingElement();
            }
            break;
		}
		element = element->NextSiblingElement(); // aller à l'élément suivant
	}
    delete sides; delete element;

    return std::string("Default");
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
