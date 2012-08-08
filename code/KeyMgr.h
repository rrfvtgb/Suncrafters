#ifndef KEYMGR_H
#define KEYMGR_H

#include <OIS/OIS.h>

#include "BaseApplication.h"
#include "PlayerMgr.h"

#include <map>

class KeyMgr
{
    public:
        KeyMgr();
        virtual ~KeyMgr();
        bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);
        void setKeyMap();

        void setPlayer(PlayerMgr* player){this->mPlayer = player;}

    protected:
    private:
        PlayerMgr* mPlayer;
        Ogre::Vector3 mDirection;

        std::ofstream flux;
        std::string mPathTokeyFile;
        std::map <std::string, int> mKeyMap;
};

#endif // KEYMGR_H
