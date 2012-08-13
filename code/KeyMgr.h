#ifndef KEYMGR_H
#define KEYMGR_H

#include <OIS/OIS.h>

#include "BaseApplication.h"
#include "PlayerMgr.h"

#include <map>
#include <fstream>

class KeyMgr
{
    public:
        KeyMgr();
        virtual ~KeyMgr();

        bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

        void setKeyMap(std::string pathToKeyFile);
        void setPlayer(PlayerMgr* player){this->mPlayer = player;}

    protected:
    private:
        PlayerMgr* mPlayer;
        Ogre::Vector3 mDirection;

        std::map <std::string, int> mKeyMap;
        std::ofstream flux;
};

#endif // KEYMGR_H
