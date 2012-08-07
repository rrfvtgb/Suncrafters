#ifndef KEYMGR_H
#define KEYMGR_H

#include <OIS/OIS.h>
#include "BaseApplication.h"
#include "PlayerMgr.h"

class KeyMgr
{
    public:
        KeyMgr();
        virtual ~KeyMgr();
        bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        void setPlayer(PlayerMgr* player){this->mPlayer = player;}

    protected:
    private:
        PlayerMgr* mPlayer;
        Ogre::Vector3 mDirection;

        std::ofstream flux;
};

#endif // KEYMGR_H
