#ifndef PLAYERMGR_H
#define PLAYERMGR_H

#include "BaseApplication.h"


class PlayerMgr
{
    public:
        PlayerMgr(Ogre::SceneManager* sceneMgr);
        virtual ~PlayerMgr();
        void addPlayer(int x, int y, int z);
        void walkTo(Ogre::Vector3 relativeCoord);
        void endWalk(Ogre::Vector3 relativeCoord);

        void setAnim(std::string anim);

        Ogre::AnimationState* mBaseAnim;
        Ogre::AnimationState* mTopAnim;
        Ogre::Entity* mEnt;

        Ogre::SceneNode* mCameraNode;
        Ogre::SceneNode* mCameraYawNode;
        Ogre::SceneNode* mCameraPitchNode;
        Ogre::SceneNode* mCameraRollNode;
        Ogre::SceneNode* mPlayerNode;

        bool mWalking;
        Ogre::Vector3 mDirection;
        Ogre::Vector3 mDestination;
        Ogre::Real mDistance;
        Ogre::Vector3 mLastrelativeCoord; //While isn't released when mDistance hits 0 use walkTo
        int mKeyPressed;
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;
        std::ofstream flux;
};

#endif // PLAYERMGR_H
