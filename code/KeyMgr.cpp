#include "KeyMgr.h"
#include "tinyXml/XmlMgr.h"
#include "PathMgr.h"

KeyMgr::KeyMgr() /*: flux(std::string("report.txt").c_str())*/{
    mDirection = Ogre::Vector3::ZERO;

    std::string pathTokeyFile = PathMgr::getDataStorageFolder() + "/config/keys.xml";
    this->setKeyMap(pathTokeyFile);
}

bool KeyMgr::keyPressed(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_ESCAPE: return false; break;
        case OIS::KC_PGUP:   this->mDirection.y += 50; this->mPlayer->AddHeight(50); this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection); break;
        case OIS::KC_PGDOWN: this->mDirection.y -= 50; this->mPlayer->AddHeight(-50); this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection); break;
        default: break;
    }

    if(e.key == this->mKeyMap["front"]){ this->mDirection.z += 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}
    if(e.key == this->mKeyMap["back"]){  this->mDirection.z -= 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}
    //Since Player isn't facing the camera directions are inversed
    if(e.key == this->mKeyMap["right"]){ this->mDirection.x -= 50; this->mPlayer->mKeyPressed++;this->mPlayer->walkTo(this->mDirection);}
    if(e.key == this->mKeyMap["left"]){  this->mDirection.x += 50; this->mPlayer->mKeyPressed++; this->mPlayer->walkTo(this->mDirection);}

    if(e.key == this->mKeyMap["jump"] && (this->mPlayer->getTopAnimId() == Player::ANIM_IDLE_TOP || this->mPlayer->getTopAnimId() == Player::ANIM_RUN_TOP)){
        this->mPlayer->setBaseAnimation(Player::ANIM_JUMP_START, true);
        this->mPlayer->setTopAnimation(Player::ANIM_NONE);
        this->mPlayer->setTimer(0);
    }
    if (e.key == this->mKeyMap["drawSwords"] && (this->mPlayer->getTopAnimId() == Player::ANIM_IDLE_TOP || this->mPlayer->getTopAnimId() == Player::ANIM_RUN_TOP)){
        // take swords out (or put them back, since it's the same animation but reversed)
        this->mPlayer->setTopAnimation(SinbadCharacter::ANIM_DRAW_SWORDS, true);
        this->mPlayer->setTimer(0);
    }
    return true;
}


bool KeyMgr::keyReleased(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_PGUP:   this->mDirection.y -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection); break;
        case OIS::KC_PGDOWN: this->mDirection.y += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection); break;
        default: break;
    }

    if(e.key ==  this->mKeyMap["front"]){ this->mDirection.z -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["back"]){  this->mDirection.z += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["right"]){ this->mDirection.x += 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    if(e.key ==  this->mKeyMap["left"]){  this->mDirection.x -= 50; this->mPlayer->mKeyPressed--; this->mPlayer->endWalk(this->mDirection);}
    return true;
}

bool KeyMgr::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id){

    if (this->mPlayer->mPlayer->mSwordsDrawn && (this->mPlayer->getTopAnimId() == Player::ANIM_IDLE_TOP || this->mPlayer->getTopAnimId() == Player::ANIM_RUN_TOP)){
        // if swords are out, and character's not doing something weird, then SLICE!
        if (id == OIS::MB_Left) this->mPlayer->setTopAnimation(SinbadCharacter::ANIM_SLICE_VERTICAL, true);
        else if (id == OIS::MB_Right) this->mPlayer->setTopAnimation(SinbadCharacter::ANIM_SLICE_HORIZONTAL, true);
        this->mPlayer->setTimer(0);
    }
    return true;
}

bool KeyMgr::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
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
