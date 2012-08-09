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
    this->mPlayerNode->attachObject(mEnt);

    this->mPlayerNode->scale(17, 17, 17);
    this->mPlayerNode->setPosition(x, y, z);
    this->mCameraRollNode->yaw(Ogre::Degree(180));

    //ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

    this->setAnim("Idle");
}

void PlayerMgr::walkTo(Ogre::Vector3 relativeCoord){
    this->mLastrelativeCoord = relativeCoord;
    this->setAnim("Run");
    this->mDirection = relativeCoord;
    this->mDirection.normalise();
    this->mWalking = true;
}
void PlayerMgr::endWalk(Ogre::Vector3 relativeCoord){
    if(this->mKeyPressed == 0){
        this->mWalking = false;
        this->setAnim("Idle");
        this->mDirection = Ogre::Vector3::ZERO;
    }else{
        this->walkTo(relativeCoord);
    }
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
