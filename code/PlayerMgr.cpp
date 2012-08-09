#include "PlayerMgr.h"

PlayerMgr::PlayerMgr(Ogre::SceneManager* sceneMgr) : flux(std::string("report.txt").c_str()){
    this->mSceneMgr = sceneMgr;
    PlayerMgr::playerNumber++;

    //walking variables
    this->mWalking = false;
    this->mDirection = Ogre::Vector3::ZERO;
    this->mKeyPressed = 0;
}

void PlayerMgr::createPlayer(Ogre::Vector3 playerPosition){
    this->mPlayerNode = sceneMgr->getRootSceneNode()
        ->createChildSceneNode(std::string("playerNode-" + Ogre::StringConverter::toString(PlayerMgr::playerNumber)));

    mEnt  = mSceneMgr->createEntity(std::string("player-" + Ogre::StringConverter::toString(PlayerMgr::playerNumber)), "Sinbad.mesh");
    this->mPlayerNode->attachObject(mEnt);

    this->mPlayerNode->scale(17, 17, 17);
    this->mPlayerNode->setPosition(playerPosition);

    //ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE); //cant seem to find ANIMBLEND_CUMULATIVE
    this->setAnim("Idle");
}

void PlayerMgr::initializeCameraNodes(void){
    this->mCameraPitchNode = this->mPlayerNode->createChildSceneNode();
    this->mCameraRollNode  = this->mCameraPitchNode->createChildSceneNode();
    this->mCameraRollNode->yaw(Ogre::Degree(180));
}

void PlayerMgr::walkTo(Ogre::Vector3 direction){
    this->setAnim("Run");

    this->mDirection = direction;
    this->mDirection.normalise();
    this->mWalking = true;
}

void PlayerMgr::endWalk(Ogre::Vector3 direction){
    if(this->mKeyPressed == 0){//Don't stop anim if 2 keys are pressed and one is released
        this->mWalking = false;
        this->mDirection = Ogre::Vector3::ZERO;

        this->setAnim("Idle");
    }else{
        this->walkTo(direction);
    }
}

void PlayerMgr::setPlayerAnimTo(std::string anim){
    mBaseAnim = mEnt->getAnimationState(std::string(anim + "Base"));
    mTopAnim = mEnt->getAnimationState(std::string(anim + "Top"));

    mBaseAnim->setLoop(true);
    mTopAnim->setLoop(true);

    mBaseAnim->setEnabled(true);
    mTopAnim->setEnabled(true);
}
PlayerMgr::~PlayerMgr(){
    delete this->mSceneMgr;

    delete mEnt;
    delete mBaseAnim;
    delete mTopAnim;

    delete mCameraPitchNode;
    delete mCameraRollNode;
    delete mPlayerNode;
}