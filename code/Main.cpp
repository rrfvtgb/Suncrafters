#include "Main.h"
#include "LevelManager.h"

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
    Ogre::ManualObject block("block");

    block.begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);
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

    LevelManager* lvl = new LevelManager(mSceneMgr);
    lvl->createWorld();


    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
}
