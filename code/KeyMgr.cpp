#include "KeyMgr.h"
#include "tinyXml/XmlMgr.h"
#include "PathMgr.h"

KeyMgr::KeyMgr() : flux(std::string("report.txt").c_str()){
    mDirection = Ogre::Vector3::ZERO;

    std::string pathTokeyFile = PathMgr::getDataStorageFolder() + "/config/keys.xml";
    this->setKeyMap(pathTokeyFile);
}

bool KeyMgr::keyPressed(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_ESCAPE: return false; break;
        case OIS::KC_PGUP:   this->mDirection.y += 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection); break;
        case OIS::KC_PGDOWN: this->mDirection.y -= 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection); break;
    }

    if(e.key ==  this->mKeyMap["front"]){ this->mDirection.z += 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}
    if(e.key ==  this->mKeyMap["back"]){  this->mDirection.z -= 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}
    //Since Player isn't facing the camera directions are inversed
    if(e.key ==  this->mKeyMap["right"]){ this->mDirection.x -= 50; this->mPlayer->mKeyPressed++;this->mPlayer->walkTo(this->mDirection);}
    if(e.key ==  this->mKeyMap["left"]){  this->mDirection.x += 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}
    return true;
}


bool KeyMgr::keyReleased(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_PGUP:   this->mDirection.y -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection); break;
        case OIS::KC_PGDOWN: this->mDirection.y += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection); break;
    }

    if(e.key ==  this->mKeyMap["front"]){ this->mDirection.z -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["back"]){  this->mDirection.z += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["right"]){ this->mDirection.x += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["left"]){  this->mDirection.x -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    return true;
}


void KeyMgr::setKeyMap(std::string pathTokeyFile){

    XmlMgr* xmlManager = new XmlMgr();
    xmlManager->loadFile(pathTokeyFile);

    TiXmlElement* element = xmlManager->getDocumentFirstChildElement();

    if(!element){this->flux << "No root node or root node haven't got any child nodes" << std::endl;return;}

	while (element){
		this->mKeyMap.insert(std::pair<std::string, int>(std::string(element->Attribute("id")), Ogre::StringConverter::parseInt(element->GetText())));
        element = element->NextSiblingElement();
    }
    delete element;
    delete xmlManager;
}

KeyMgr::~KeyMgr(){
    delete this->mPlayer;
}
