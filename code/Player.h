#ifndef PLAYER_H
#define PLAYER_H

#include "BaseApplication.h"

#include <vector>

#define NUM_ANIMS 7           // number of animations the base character has
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 180.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 190.0f          // gravity in downward units per squared second

class Player
{
    public:
        enum AnimID{
            ANIM_IDLE_BASE,
            ANIM_IDLE_TOP,
            ANIM_RUN_BASE,
            ANIM_RUN_TOP,
            ANIM_JUMP_START,
            ANIM_JUMP_LOOP,
            ANIM_JUMP_END,
            ANIM_NONE
        };

        Player();
        virtual ~Player();

        virtual void setupAnimations();//should be overriten if there is more anims
        virtual void createPlayer(Ogre::Vector3 playerPosition, Ogre::SceneNode* playerNode, Ogre::Entity* ent) = 0;//override me !

        virtual void updateBody(Ogre::Real deltaTime);

        virtual void updateAnimations(Ogre::Real deltaTime);
        void fadeAnimations(Ogre::Real deltaTime);

        virtual void setBaseAnimation(int id, bool reset = false);
        virtual void setTopAnimation(int id, bool reset = false);

        std::vector <Ogre::AnimationState *> mAnims;    // master animation list
        int mBaseAnimID;             // current base (full- or lower-body) animation
        int mTopAnimID;              // current top (upper-body) animation
        bool mFadingIn[NUM_ANIMS];            // which animations are fading in
        bool mFadingOut[NUM_ANIMS];           // which animations are fading out

        Ogre::Real mTimer;
        Ogre::Entity* mEnt;
        Ogre::SceneNode* mPlayerNode;

        bool mWalking;
        bool mJumping;
        int mCurrentheight;

        Ogre::Real mBaseAnimSpeed;
        Ogre::Real mTopAnimSpeed;

        bool mSwordsDrawn;

        Ogre::SceneManager* mSceneMgr;
    protected:
    private:
        Ogre::Real mVerticalVelocity;
};

#endif // PLAYER_H
