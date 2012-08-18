#include "Main.h"
#include "LevelManager.h"
#include "InputListener.h"

Main::Main()
{
    //ctor
}

Main::~Main()
{
    //dtor
}
void Main::createScene(void)
{
    srand(time(NULL));
    Ogre::ManualObject block("block");

    block.begin("Default", Ogre::RenderOperation::OT_TRIANGLE_LIST);
		block.position(-50, 100, 0);
		block.textureCoord(0, 0);

		block.position(50, 100, 0);
		block.textureCoord(1, 0);

		block.position(-50, 0, 0);
		block.textureCoord(0, 1);

		block.position(50, 0, 0);
		block.textureCoord(1, 1);

		block.triangle(0, 3, 1);
		block.triangle(0, 2, 3);
    block.end();
    block.convertToMesh("blockMesh");


    mSceneMgr->getRootSceneNode()->createChildSceneNode("LandscapeMgrNode");

    LevelManager* lvl = new LevelManager(mSceneMgr);
    lvl->createWorld();

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

    mPlayer = new PlayerMgr(mSceneMgr);
    mPlayer->createPlayer(Ogre::Vector3(0, 85, 0), PlayerMgr::Sinbad);
}

void Main::createFrameListener(void){
    InputListener* frameListener = new InputListener(mWindow, mCamera, mSceneMgr, true, true, false);
    frameListener->addPlayer(mPlayer);
    mRoot->addFrameListener(frameListener);
}
