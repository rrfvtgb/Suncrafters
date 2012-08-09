#include "KeyMgr.h"
#include "tinyXml/tinyxml.h"
#include "PathMgr.h"

KeyMgr::KeyMgr() : flux(std::string("report.txt").c_str()){
    mDirection = Ogre::Vector3::ZERO;

    this->mPathTokeyFile = PathMgr::getDataStorageFolder() + "/config/keys.xml";
    this->setKeyMap();
}

bool KeyMgr::keyPressed(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_ESCAPE:
            return false;
        break;
        case OIS::KC_PGUP:
            this->mDirection.y += 50;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_PGDOWN:
            this->mDirection.y -= 50;
            this->mPlayer->walkTo(this->mDirection);
        break;
    }
    if(e.key ==  this->mKeyMap["front"]){
        this->mDirection.z += 50;
        this->mPlayer->walkTo(this->mDirection);
    }
    if(e.key ==  this->mKeyMap["back"]){
        this->mDirection.z -= 50;
        this->mPlayer->walkTo(this->mDirection);
    }
    if(e.key ==  this->mKeyMap["right"]){
        this->mDirection.x += 50;
        this->mPlayer->walkTo(this->mDirection);
    }
    if(e.key ==  this->mKeyMap["left"]){
        this->mDirection.x -= 50;
        this->mPlayer->walkTo(this->mDirection);
    }
}
bool KeyMgr::keyReleased(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_PGUP:   this->mDirection.y -= 50; this->mPlayer->endWalk(this->mDirection); break;
        case OIS::KC_PGDOWN: this->mDirection.y += 50; this->mPlayer->endWalk(this->mDirection); break;
    }
    if(e.key ==  this->mKeyMap["front"]){ this->mDirection.z -= 50; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["back"]){  this->mDirection.z += 50; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["right"]){ this->mDirection.x -= 50; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["left"]){  this->mDirection.x += 50; this->mPlayer->endWalk(this->mDirection);}
    return true;
}
void KeyMgr::setKeyMap(){
    TiXmlDocument* document = new TiXmlDocument(this->mPathTokeyFile.c_str());
    if(!document->LoadFile()){
        this->flux << "error while loading" << std::endl;
        this->flux << "error #" << document->ErrorId() << " : " << document->ErrorDesc() << std::endl;
        return;
    }
    TiXmlHandle* hdl = new TiXmlHandle(document);
    TiXmlElement* element = hdl->FirstChildElement().FirstChildElement().ToElement();

    if(!element){
		this->flux << "No root node or root node haven't got any child nodes" << std::endl;
		return;
    }

	while (element){
		this->mKeyMap.insert(std::pair<std::string, int>(std::string(element->Attribute("id")), Ogre::StringConverter::parseInt(element->GetText())));
        element = element->NextSiblingElement();
    }
    delete element;
    delete hdl;
    delete document;
}

KeyMgr::~KeyMgr()
{
    //dtor
}
