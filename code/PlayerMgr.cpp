#include "PlayerMgr.h"

PlayerMgr::PlayerMgr(Ogre::SceneManager* sceneMgr) : flux(std::string("report.txt").c_str()){
    this->mSceneMgr = sceneMgr;

    this->mPlayerNode = sceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");

    this->mCameraPitchNode = this->mPlayerNode->createChildSceneNode();
    this->mCameraRollNode  = this->mCameraPitchNode->createChildSceneNode();

    this->mWalking = false;
    this->mDirection = Ogre::Vector3::ZERO;
    this->mDistance = 0;
    this->mKeyPressed = 0;
}

void PlayerMgr::addPlayer(int x, int y, int z){

    mEnt  = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
    mPlayerNode->attachObject(mEnt);

    mPlayerNode->scale(17, 17, 17);
    mPlayerNode->setPosition(x, y, z);

    //ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    this->setAnim("Idle");
}

void PlayerMgr::walkTo(Ogre::Vector3 relativeCoord){
    this->mLastrelativeCoord = relativeCoord;

    this->mDestination += relativeCoord;
    this->mDirection = this->mDestination - this->mPlayerNode->getPosition();
    this->mDistance = this->mDirection.normalise();
    this->mWalking = true;
}
void PlayerMgr::endWalk(Ogre::Vector3 relativeCoord){

    this->mWalking = false;
    this->setAnim("Idle");
    this->mDirection = Ogre::Vector3::ZERO;
    this->mDestination = this->mPlayerNode->getPosition();
    this->mDistance = 0;
}
void PlayerMgr::setAnim(std::string anim){
    mBaseAnim = mEnt->getAnimationState(std::string(anim + "Base"));
    mTopAnim = mEnt->getAnimationState(std::string(anim + "Top"));

    mBaseAnim->setLoop(true);
    mTopAnim->setLoop(true);

    mBaseAnim->setEnabled(true);
    mTopAnim->setEnabled(true);
}
PlayerMgr::~PlayerMgr(){
    delete this->mSceneMgr;
}
