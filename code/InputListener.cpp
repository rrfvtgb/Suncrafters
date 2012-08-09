#include "InputListener.h"

InputListener::InputListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneManager *sceneMgr,
                             bool bufferedKeys, bool bufferedMouse, bool bufferedJoy):
                             ExampleFrameListener(win, cam, bufferedKeys, bufferedMouse, bufferedJoy), flux(std::string("report.txt").c_str()){

    this->mSceneMgr = sceneMgr;
    this->mShutDown = true;
    this->mMvt = new Ogre::Vector3(0, 0, 0);
    this->mKeyManager = new KeyMgr();
    this->walkSpeed = 200.0f;

    this->mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);
}
bool InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt){
    if(mMouse)
        mMouse->capture();
    if(mKeyboard)
        mKeyboard->capture();

    for(int i = 0, l = this->mPlayerList.size(); i < l; i++){
        this->mPlayerList[i]->mBaseAnim->addTime(evt.timeSinceLastEvent);
        this->mPlayerList[i]->mTopAnim->addTime(evt.timeSinceLastEvent);

        if(this->mPlayerList[i]->mWalking){
            //this->mPlayerList[i]->mDistance -= this->walkSpeed * evt.timeSinceLastFrame;
            flux << "pos : " <<this->mPlayerList[i]->mPlayerNode->getPosition() << std::endl;
            if(this->mPlayerList[i]->mDistance <= 0){
                this->mPlayerList[i]->walkTo(this->mPlayerList[i]->mLastrelativeCoord);
            }else{
                this->mPlayerList[i]->setAnim("Run");
                this->mPlayerList[i]->mPlayerNode->translate(this->mPlayerList[i]->mDirection * this->walkSpeed * evt.timeSinceLastFrame, Ogre::SceneNode::TS_LOCAL);
            }

        }
    }

    return mShutDown;
}

bool InputListener::mouseMoved(const OIS::MouseEvent &e){


    const OIS::MouseState &mouseState = mMouse->getMouseState();
    this->mRotX = Ogre::Degree(-mouseState.X.rel * 0.13);
    this->mRotY = Ogre::Degree(-mouseState.Y.rel * 0.13);

    /*flux << "rot Y : " << this->mPlayerList[0]->mCameraPitchNode->getOrientation() << std::endl;
    flux << "rot Y : " << this->mPlayerList[0]->mCameraNode->getPosition() << std::endl << std::endl;*/

    Ogre::Real pitchAngle;
    Ogre::Real pitchAngleSign;

    this->mPlayerList[0]->mPlayerNode->yaw(this->mRotX);
    this->mPlayerList[0]->mCameraPitchNode->pitch(this->mRotY);

    this->mPlayerList[0]->mPlayerNode->translate(this->mPlayerList[0]->mPlayerNode->getOrientation() * this->mPlayerList[0]->mCameraPitchNode->getOrientation()
                                          * this->mTranslateVector, Ogre::SceneNode::TS_LOCAL);

    pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(this->mPlayerList[0]->mCameraPitchNode->getOrientation().w)).valueDegrees());

    pitchAngleSign = this->mPlayerList[0]->mCameraPitchNode->getOrientation().x;

    if(pitchAngle > 90.0f){
        if(pitchAngleSign > 0){
            this->mPlayerList[0]->mCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), Ogre::Math::Sqrt(0.5f), 0, 0));
        }else if(pitchAngle < 0){
            this->mPlayerList[0]->mCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), -Ogre::Math::Sqrt(0.5f), 0, 0));
        }
    }
    return true;
}
bool InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id){
    return true;
}
bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
    return true;
}
bool InputListener::keyPressed(const OIS::KeyEvent &e){
    if(this->mKeyManager->keyPressed(e)){
        return true;
    }else{
        this->mShutDown = false;
        return true;
    }
}
bool InputListener::keyReleased(const OIS::KeyEvent &e){
    return this->mKeyManager->keyReleased(e);
}

void InputListener::setPlayer(PlayerMgr* player){
    this->mPlayerList.push_back(player);
    player->mDestination = player->mPlayerNode->getPosition();
    if(this->mPlayerList.size() == 1){
        this->mKeyManager->setPlayer(player);
        player->mCameraRollNode->attachObject(this->mCamera);
    }
}
