#include "PlayerMgr.h"

PlayerMgr::PlayerMgr(Ogre::SceneManager* sceneMgr){
    this->mSceneMgr = sceneMgr;

    this->mCameraNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    this->mCameraNode->setPosition(0, 0, 500);

    this->mCameraYawNode   = this->mCameraNode->createChildSceneNode();
    this->mCameraPitchNode = this->mCameraYawNode->createChildSceneNode();
    this->mCameraRollNode  = this->mCameraPitchNode->createChildSceneNode();

    this->mWalking = false;
    this->mDirection = Ogre::Vector3::ZERO;
    this->mDestination = this->mCameraNode->getPosition();
    this->mDistance = 0;
}

void PlayerMgr::addPlayer(int x, int y, int z){

    mPlayerNode = this->mCameraYawNode->createChildSceneNode("playerNode");
    mEnt  = mSceneMgr->createEntity("Sinbad", "Sinbad.mesh");
    mPlayerNode->attachObject(mEnt);

    mPlayerNode->scale(17, 17, 17);
    mPlayerNode->setPosition(x, y, z);
    mPlayerNode->yaw(Ogre::Degree(180));

    //ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    this->setAnim("Idle");
}

void PlayerMgr::walkTo(Ogre::Vector3 direction){
    this->mWalking = true;
    this->mDirection += direction;
    this->mDestination += direction;
    this->mDistance += direction.normalise();
}
void PlayerMgr::endWalk(){
    this->mWalking = false;
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
