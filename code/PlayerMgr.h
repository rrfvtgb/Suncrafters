#ifndef PLAYERMGR_H
#define PLAYERMGR_H

#include "BaseApplication.h"
#include "Player.h"
#include "characters/SinbadCharacter.h"

#include <fstream>


class PlayerMgr
{
    public:
        enum Characters{
            Sinbad
        };
        PlayerMgr(Ogre::SceneManager* sceneMgr);
        virtual ~PlayerMgr();

        void addTime(Ogre::Real deltaTime);
        void createPlayer(Ogre::Vector3 playerPosition, Characters playerType = PlayerMgr::Sinbad);
        void initializeCameraNodes(void);

        void walkTo(Ogre::Vector3 direction);
        void endWalk(Ogre::Vector3 direction);

        int getTopAnimId();
        int getBaseAnimId();

        Ogre::AnimationState* getTopAnimState();
        Ogre::AnimationState* getBaseAnimState();

        void setBaseAnimation(int id, bool reset = false);
        void setTopAnimation(int id, bool reset = false);

        bool isWalking();
        void setWalking(bool walk);
        bool isJumping();

        int getTimer();
        void setTimer(int time);

        void AddHeight(int height);

        Ogre::Entity* mEnt;

        Ogre::SceneNode* mCameraPitchNode;
        Ogre::SceneNode* mCameraRollNode;
        Ogre::SceneNode* mPlayerNode;

        Ogre::Vector3 mDirection;
        Player* mPlayer;

        int mKeyPressed;//Don't stop walking if 2 keys are pressed and one is released

        static int playerNumber;
    protected:
    private:
        Ogre::SceneManager* mSceneMgr;

        std::ofstream flux;
};

#endif // PLAYERMGR_H
