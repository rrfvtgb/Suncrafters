#include "PlayerMgr.h"
class PlayerMgrFactory{
    public:
        Player* makePlayer(PlayerMgr::Characters playerType, Ogre::SceneManager* sceneMgr){
            switch(playerType){
                case PlayerMgr::Sinbad: return new SinbadCharacter(sceneMgr); break;
            }
            return new SinbadCharacter(sceneMgr);
        }
};

int PlayerMgr::playerNumber = 0;

PlayerMgr::PlayerMgr(Ogre::SceneManager* sceneMgr) : flux(std::string("report/playerMgr.txt").c_str()), mPlayerNode(0){
    this->mSceneMgr = sceneMgr;
    PlayerMgr::playerNumber++;

    //walking variables
    this->mDirection = Ogre::Vector3::ZERO;
    this->mKeyPressed = 0;
    flux << "-3" << std::endl;
}
void PlayerMgr::addTime(Ogre::Real deltaTime){
    this->mPlayer->updateBody(deltaTime);
    this->mPlayer->updateAnimations(deltaTime);
}
void PlayerMgr::createPlayer(Ogre::Vector3 playerPosition, Characters playerType){

    PlayerMgrFactory* playerFactory = new PlayerMgrFactory();
    this->mPlayer = playerFactory->makePlayer(playerType, this->mSceneMgr);

    this->mPlayer->createPlayer(playerPosition, this->mPlayerNode, this->mEnt);
    this->mPlayerNode = this->mSceneMgr->getSceneNode("playerNode");


    if(PlayerMgr::playerNumber == 1){
        this->initializeCameraNodes();
    }
}

void PlayerMgr::initializeCameraNodes(void){
    flux << "0" << std::endl;
    //flux << "name : " << this->mPlayerNode->getName() << std::endl;
    if(this->mPlayerNode != NULL){
        flux << "0.01" << std::endl;
        this->mCameraPitchNode = this->mPlayerNode->createChildSceneNode();
    }flux << "0.1" << std::endl;
    this->mCameraRollNode  = this->mCameraPitchNode->createChildSceneNode();
    flux << "0.2" << std::endl;
    this->mCameraRollNode->yaw(Ogre::Degree(180));
    //this->mCameraRollNode->translate(0, 3, 32);
    flux << "1" << std::endl;
}

void PlayerMgr::walkTo(Ogre::Vector3 direction){
    this->setBaseAnimation(Player::ANIM_RUN_BASE);
    this->setTopAnimation(Player::ANIM_RUN_TOP);

    this->mDirection = direction;
    this->mDirection.normalise();
    this->setWalking(true);
}

void PlayerMgr::endWalk(Ogre::Vector3 direction){
    if(this->mKeyPressed == 0){//Don't stop anim if 2 keys are pressed and one is released
        this->setWalking(false);
        this->mDirection = Ogre::Vector3::ZERO;

        this->setBaseAnimation(Player::ANIM_IDLE_BASE);
        this->setTopAnimation(Player::ANIM_IDLE_TOP);
    }
    else{this->walkTo(direction);}
}

int PlayerMgr::getTopAnimId(){
    return this->mPlayer->mTopAnimID;
}

int PlayerMgr::getBaseAnimId(){
    return this->mPlayer->mBaseAnimID;
}

Ogre::AnimationState* PlayerMgr::getTopAnimState(){
    return this->mPlayer->mAnims[this->getTopAnimId()];
}

Ogre::AnimationState* PlayerMgr::getBaseAnimState(){
    return this->mPlayer->mAnims[this->getBaseAnimId()];
}

void PlayerMgr::setTopAnimation(int id, bool reset){
    this->mPlayer->setTopAnimation(id, reset);
}

void PlayerMgr::setBaseAnimation(int id, bool reset){
    this->mPlayer->setBaseAnimation(id, reset);
}

bool PlayerMgr::isWalking(){
    return this->mPlayer->mWalking;
}
void PlayerMgr::setWalking(bool walk){
    this->mPlayer->mWalking = walk;
}
bool PlayerMgr::isJumping(){
    return this->mPlayer->mJumping;
}

int PlayerMgr::getTimer(){
    return this->mPlayer->mTimer;
}
void PlayerMgr::setTimer(int time){
    this->mPlayer->mTimer = time;
}

void PlayerMgr::AddHeight(int height){
    this->mPlayer->mCurrentheight += height;
}

PlayerMgr::~PlayerMgr(){
    delete this->mSceneMgr;

    delete mEnt;

    delete mCameraPitchNode;
    delete mCameraRollNode;
    delete mPlayerNode;
}
