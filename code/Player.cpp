#include "Player.h"

Player::Player(){}


void Player::setupAnimations(){
    std::string animNames[] = {"IdleBase", "IdleTop", "RunBase", "RunTop", "JumpStart", "JumpLoop", "JumpEnd"};

    for (int i = 0; i < NUM_ANIMS; i++){
        this->mAnims.push_back(mEnt->getAnimationState(animNames[i]));
        this->mAnims[i]->setLoop(true);
        this->mFadingIn[i] = false;
        this->mFadingOut[i] = false;
    }
    // start off in the idle state (top and bottom together)
    this->setBaseAnimation(ANIM_IDLE_BASE);
    this->setTopAnimation(ANIM_IDLE_TOP);
}

void Player::updateBody(Ogre::Real deltaTime)
{
    if (this->mBaseAnimID == ANIM_JUMP_LOOP)
    {
        // if we're jumping, add a vertical offset too, and apply gravity
        this->mPlayerNode->translate(0, mVerticalVelocity * deltaTime, 0, Ogre::Node::TS_LOCAL);
        this->mVerticalVelocity -= GRAVITY * deltaTime;

        Ogre::Vector3 pos = this->mPlayerNode->getPosition();
        if (pos.y <= this->mCurrentheight)
        {
            // if we've hit the ground, change to landing state
            pos.y = this->mCurrentheight;
            this->mPlayerNode->setPosition(pos);
            this->setBaseAnimation(ANIM_JUMP_END, true);
            mTimer = 0;
        }
    }
}

void Player::updateAnimations(Ogre::Real deltaTime){
    if (this->mBaseAnimID == ANIM_JUMP_START){
        this->mJumping = true;
        if (this->mTimer >= this->mAnims[mBaseAnimID]->getLength()){
            this->setBaseAnimation(ANIM_JUMP_LOOP, true);// takeoff animation finished, so time to leave the ground!
            this->mVerticalVelocity = JUMP_ACCEL;// apply a jump acceleration to the character
        }
    }
    else if (this->mBaseAnimID == ANIM_JUMP_END){
        if (this->mTimer >= mAnims[mBaseAnimID]->getLength()){
            this->mJumping = false;
            if (!this->mWalking){// safely landed, so go back to running or idling
                this->setBaseAnimation(ANIM_IDLE_BASE);
                this->setTopAnimation(ANIM_IDLE_TOP);
            }else{
                this->setBaseAnimation(ANIM_RUN_BASE, true);
                this->setTopAnimation(ANIM_RUN_TOP, true);
            }
        }
    }
    if (this->mBaseAnimID != ANIM_NONE) this->mAnims[this->mBaseAnimID]->addTime(deltaTime * mBaseAnimSpeed);// increment the current base and top animation times
    if (this->mTopAnimID != ANIM_NONE) this->mAnims[this->mTopAnimID]->addTime(deltaTime * mTopAnimSpeed);

    fadeAnimations(Ogre::Real(deltaTime));// apply smooth transitioning between our animations

}

void Player::setBaseAnimation(int id, bool reset)
{
    if (this->mBaseAnimID >= 0 && this->mBaseAnimID < (int)this->mAnims.size()){
        // if we have an old animation, fade it out
        this->mFadingIn[mBaseAnimID] = false;
        this->mFadingOut[mBaseAnimID] = true;
    }

    this->mBaseAnimID = id;

    if (id != ANIM_NONE && this->mBaseAnimID < (int)this->mAnims.size()){
        // if we have a new animation, enable it and fade it in
        this->mAnims[id]->setEnabled(true);
        this->mAnims[id]->setWeight(0);
        this->mFadingOut[id] = false;
        this->mFadingIn[id] = true;
        if (reset) this->mAnims[id]->setTimePosition(0);
    }
}

void Player::setTopAnimation(int id, bool reset)
{
    if (this->mTopAnimID >= 0){
        this->mFadingIn[mTopAnimID] = false;// if we have an old animation, fade it out
        this->mFadingOut[mTopAnimID] = true;
    }

    mTopAnimID = id;

    if (id != ANIM_NONE){
        this->mAnims[id]->setEnabled(true);// if we have a new animation, enable it and fade it in
        this->mAnims[id]->setWeight(0);
        this->mFadingOut[id] = false;
        this->mFadingIn[id] = true;
        if (reset) this->mAnims[id]->setTimePosition(0);
    }
}
void Player::fadeAnimations(Ogre::Real deltaTime){
    for (int i = 0; i < NUM_ANIMS; i++){
        if (mFadingIn[i])
        {
            // slowly fade this animation in until it has full weight
            Ogre::Real newWeight = this->mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
            this->mAnims[i]->setWeight(Ogre::Math::Clamp<Ogre::Real>(newWeight, 0, 1));
            if (newWeight >= 1) this->mFadingIn[i] = false;
        }
        else if (mFadingOut[i])
        {
            // slowly fade this animation out until it has no weight, and then disable it
            Ogre::Real newWeight = this->mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
            this->mAnims[i]->setWeight(Ogre::Math::Clamp<Ogre::Real>(newWeight, 0, 1));
            if (newWeight <= 0)
            {
                this->mAnims[i]->setEnabled(false);
                this->mFadingOut[i] = false;
            }
        }
    }
}
Player::~Player(){
    delete this->mEnt;
    delete this->mPlayerNode;
    this->mAnims.clear();
}
