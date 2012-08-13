#include "SinbadCharacter.h"

SinbadCharacter::SinbadCharacter(Ogre::SceneManager* sceneMgr) : flux(std::string("report/report.txt").c_str()){
    this->mSceneMgr = sceneMgr;
}

void SinbadCharacter::createPlayer(Ogre::Vector3 playerPosition, Ogre::SceneNode* playerNode, Ogre::Entity* ent){

    this->mEnt = ent;
    this->mPlayerNode = playerNode;

    flux << "0" << std::endl;
    flux << &mPlayerNode << std::endl;

    playerNode    = this->mSceneMgr->getRootSceneNode()->createChildSceneNode("playerNode");

    this->mPlayerNode = playerNode;
    this->mEnt    = this->mSceneMgr->createEntity(std::string("player"), "Sinbad.mesh");

    flux << "1" << std::endl;

    this->mPlayerNode->attachObject(mEnt);

    flux << "2" << std::endl;

    mSword1 = this->mSceneMgr->createEntity("SinbadSword1", "Sword.mesh");
    mSword2 = this->mSceneMgr->createEntity("SinbadSword2", "Sword.mesh");

    mEnt->attachObjectToBone("Sheath.L", mSword1);
    mEnt->attachObjectToBone("Sheath.R", mSword2);

    //this->mEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE); //cant seem to find ANIMBLEND_CUMULATIVE
    flux << "3" << std::endl;

    this->mPlayerNode->scale(17, 17, 17);
    this->mPlayerNode->setPosition(playerPosition);
    this->mCurrentheight = playerPosition.y;
    this->setupAnimations();
    flux << "4" << std::endl;


}

void SinbadCharacter::setupAnimations(){
    Player::setupAnimations();//Call Mother function before this one

    std::string animNames[] = {"HandsClosed", "HandsRelaxed", "DrawSwords", "SliceVertical", "SliceHorizontal"};

    flux << "size : " << mAnims.size() << std::endl;
    flux << "SINBAD_NUM_ANIMS : " << SINBAD_NUM_ANIMS << std::endl;

    for (int i = mAnims.size(), a = 0; i < SINBAD_NUM_ANIMS; i++, a++){//i for mAnims and a for animNames
        this->mAnims.push_back(mEnt->getAnimationState(animNames[a]));
        this->mAnims[i-1]->setLoop(true);
        this->mFadingIn[i-1] = false;
        this->mFadingOut[i-1] = false;
    }
    mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);
    mSwordsDrawn = false;
    flux << "ANIM_HANDS_RELAXED : " << ANIM_HANDS_RELAXED << std::endl;
}

void SinbadCharacter::updateAnimations(Ogre::Real deltaTime){
    this->mBaseAnimSpeed = 1;
    this->mTopAnimSpeed = 1;

    this->mTimer += deltaTime;

    if (this->mTopAnimID == ANIM_DRAW_SWORDS){
        this->mTopAnimSpeed = mSwordsDrawn ? -1 : 1;// flip the draw swords animation if we need to put it back

        // half-way through the animation is when the hand grasps the handles...
        if (this->mTimer >= this->mAnims[mTopAnimID]->getLength() / 2 &&
            this->mTimer - deltaTime < this->mAnims[mTopAnimID]->getLength() / 2){
            // so transfer the swords from the sheaths to the hands
            this->mEnt->detachAllObjectsFromBone();
            this->mEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.L" : "Handle.L", mSword1);
            this->mEnt->attachObjectToBone(mSwordsDrawn ? "Sheath.R" : "Handle.R", mSword2);
            // change the hand state to grab or let go
            this->mAnims[ANIM_HANDS_CLOSED]->setEnabled(!mSwordsDrawn);
            this->mAnims[ANIM_HANDS_RELAXED]->setEnabled(mSwordsDrawn);

        }if (this->mTimer >= this->mAnims[mTopAnimID]->getLength()){
            // animation is finished, so return to what we were doing before
            if (this->mBaseAnimID == ANIM_IDLE_BASE) this->setTopAnimation(ANIM_IDLE_TOP);
            else{
                this->setTopAnimation(ANIM_RUN_TOP);
                this->mAnims[ANIM_RUN_TOP]->setTimePosition(this->mAnims[ANIM_RUN_BASE]->getTimePosition());
            }
            mSwordsDrawn = !mSwordsDrawn;
        }
    }else if (this->mTopAnimID == ANIM_SLICE_VERTICAL || this->mTopAnimID == ANIM_SLICE_HORIZONTAL){
        if (this->mTimer >= this->mAnims[mTopAnimID]->getLength()){

            if (this->mBaseAnimID == ANIM_IDLE_BASE) this->setTopAnimation(ANIM_IDLE_TOP); // animation is finished, so return to what we were doing before
            else{
                this->setTopAnimation(ANIM_RUN_TOP);
                this->mAnims[ANIM_RUN_TOP]->setTimePosition(mAnims[ANIM_RUN_BASE]->getTimePosition());
            }
        }

        if (this->mBaseAnimID == ANIM_IDLE_BASE) this->mBaseAnimSpeed = 0;// don't sway hips from side to side when slicing. that's just embarrasing.
    }
    Player::updateAnimations(deltaTime);
}

SinbadCharacter::~SinbadCharacter(){
    delete this->mSword1;
    delete this->mSword2;
}
