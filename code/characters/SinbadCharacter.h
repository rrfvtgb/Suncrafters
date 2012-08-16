#ifndef SINBADCHARACTER_H
#define SINBADCHARACTER_H

#include "Character.h"

#define SINBAD_NUM_ANIMS NUM_ANIMS+5

class SinbadCharacter : public Character{
    public:
        enum SinbadAnimId{
            ANIM_HANDS_CLOSED = Character::ANIM_NONE,//Anim none isn't counted
            ANIM_HANDS_RELAXED,
            ANIM_DRAW_SWORDS,
            ANIM_SLICE_VERTICAL,
            ANIM_SLICE_HORIZONTAL,
        };

        SinbadCharacter(Ogre::SceneManager* sceneMgr);
        virtual ~SinbadCharacter();

        void createPlayer(Ogre::Vector3 playerPosition, Ogre::SceneNode* playerNode, Ogre::Entity* ent);
        void setupAnimations();

        void updateAnimations(Ogre::Real deltaTime);

        Ogre::Entity* mSword1;
        Ogre::Entity* mSword2;

    protected:
    private:
        std::ofstream flux;
};

#endif // SINBADCHARACTER_H
