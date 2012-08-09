#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include <ExampleFrameListener.h>
#include <OIS/OIS.h>

#include <fstream>
#include <vector>

#include "BaseApplication.h"
#include "PlayerMgr.h"
#include "KeyMgr.h"

class InputListener : public ExampleFrameListener, OIS::KeyListener, OIS::MouseListener
{
    public:
        InputListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneManager *sceneMgr,
                      bool bufferedKeys = false, bool bufferedMouse = false, bool bufferedJoy = false);
        virtual bool frameRenderingQueued(const FrameEvent& evt);

        bool mouseMoved(const OIS::MouseEvent &e);
        bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
        bool keyPressed(const OIS::KeyEvent &e);
        bool keyReleased(const OIS::KeyEvent &e);

        void setPlayer(PlayerMgr* player);
    private:
        Ogre::SceneManager *mSceneMgr;
        bool mShutDown;
        float walkSpeed;

        std::vector <PlayerMgr *> mPlayerList;
        Ogre::Vector3* mMvt;
        KeyMgr* mKeyManager;

        std::ofstream flux;
};

#endif // INPUTLISTENER_H