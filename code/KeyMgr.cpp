#include "KeyMgr.h"

KeyMgr::KeyMgr() : flux(std::string("report.txt").c_str()){
    mDirection = Ogre::Vector3::ZERO;
}

bool KeyMgr::keyPressed(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_ESCAPE:
            return false;
        break;
        case OIS::KC_PGUP:
            this->mDirection.y += 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_PGDOWN:
            this->mDirection.y -= 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_UP:
            this->mDirection.x += 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_DOWN:
            this->mDirection.x -= 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_RIGHT:
            this->mDirection.z += 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
        case OIS::KC_LEFT:
            this->mDirection.z -= 25;
            this->mPlayer->walkTo(this->mDirection);
        break;
    }
}
bool KeyMgr::keyReleased(const OIS::KeyEvent &e){
    switch(e.key){
        case OIS::KC_PGUP:   this->mDirection.y -= 25; this->mPlayer->endWalk(); break;
        case OIS::KC_PGDOWN: this->mDirection.y += 25; this->mPlayer->endWalk(); break;
        case OIS::KC_UP:     this->mDirection.x -= 25; this->mPlayer->endWalk(); break;
        case OIS::KC_DOWN:   this->mDirection.x += 25; this->mPlayer->endWalk(); break;
        case OIS::KC_RIGHT:  this->mDirection.z -= 25; this->mPlayer->endWalk(); break;
        case OIS::KC_LEFT:   this->mDirection.z += 25; this->mPlayer->endWalk(); break;
    }
    return true;
}

KeyMgr::~KeyMgr()
{
    //dtor
}
