#include "Main.h"
#include "LevelManager.h"
#include <SkyX.h>

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

    LevelManager* lvl = new LevelManager(mSceneMgr);
    lvl->createWorld();

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

    /*// Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

    //SkyX
    SkyX::BasicController* mBasicController = new SkyX::BasicController();
    SkyX::SkyX* mSkyX = new SkyX::SkyX(mSceneMgr, mBasicController);
    mSkyX->create();

    mBasicController->setMoonPhase(0.75f);

    // Register listeners
    mRoot->addFrameListener(mSkyX);
    mWindow->addListener(mSkyX);

    // Add the atmospheric scattering pass to our terrain material
    // The ground atmospheric scattering pass must be added to all materials that are going to be used to
    // render object which we want to have atmospheric scattering effects on.
    mSkyX->getGPUManager()->addGroundPass(
        static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().
        getByName("Terrain"))->getTechnique(0)->createPass(), 5000, Ogre::SBT_TRANSPARENT_COLOUR);

    // Create the terrain
    mSceneMgr->setWorldGeometry("Terrain.cfg");

    // Add a basic cloud layer
    mSkyX->getCloudsManager()->add(SkyX::CloudLayer::Options());*/
}
