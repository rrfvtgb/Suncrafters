#ifndef PLAYERMGR_H
#define PLAYERMGR_H

#include "BaseApplication.h"


class PlayerMgr
{
    public:
        PlayerMgr(Ogre::SceneManager* sceneMgr);
        virtual ~PlayerMgr();

        void createPlayer(Ogre::Vector3 playerPosition);
        void initializeCameraNodes(void);

        void walkTo(Ogre::Vector3 direction);
        void endWalk(Ogre::Vector3 direction);

        void setPlayerAnimTo(std::string anim);

        Ogre::Entity* mEnt;
        Ogre::AnimationState* mBaseAnim;//Sinbad anim has 2 anim states
        Ogre::AnimationState* mTopAnim;

        Ogre::SceneNode* mCameraPitchNode;
        Ogre::SceneNode* mCameraRollNode;
        Ogre::SceneNode* mPlayerNode;

        bool mWalking;
        Ogre::Vector3 mDirection;

        int mKeyPressed;//Don't stop anim if 2 keys are pressed and one is released
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;

        static int playerNumber;


};

#endif // PLAYERMGR_H
