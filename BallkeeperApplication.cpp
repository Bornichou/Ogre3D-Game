/*
-----------------------------------------------------------------------------
Filename:    BallkeeperApplication.cpp
-----------------------------------------------------------------------------
*/

#include "BallkeeperApplication.h"
#include "BKGameEntity.h"

#include "TextRenderer.h"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BallkeeperApplication::BallkeeperApplication(void)
{
	// Initialize random seed
	srand(time(NULL));

	m_uiCurrentLevel = 0;

	m_bManualCamera = false;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BallkeeperApplication::~BallkeeperApplication(void)
{
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool BallkeeperApplication::frameStarted(const Ogre::FrameEvent& evt)
{
	// From Base application
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();


	// Update the current level
	if(m_apLevel[m_uiCurrentLevel]->GetLeveState() == eLevelState_WarmUp)
	{
		m_apLevel[m_uiCurrentLevel]->UpdateWarmUp(evt);
	}
	if(m_apLevel[m_uiCurrentLevel]->GetLeveState() == eLevelState_Play)
	{
		m_apLevel[m_uiCurrentLevel]->UpdatePlay(evt);
	}


	if (m_apLevel[m_uiCurrentLevel]->IsFinished())
	{
		m_apLevel[m_uiCurrentLevel]->UpdateLevelEnd(evt);
		if(mKeyboard->isKeyDown(OIS::KC_RETURN))
		{
		    m_apLevel[m_uiCurrentLevel]->Stop();
		    if (m_apLevel[m_uiCurrentLevel]->IsCompleted())
            {
                m_uiCurrentLevel++;
                if (m_uiCurrentLevel >= BK_LEVEL_NB)
                {
                    // All level ended;
                    return false;
                }
            }
            TextRenderer::getSingleton().hidePanel("LevelEndPanel");
            m_apLevel[m_uiCurrentLevel]->Start();
		}

	}


    return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool BallkeeperApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	if (m_bManualCamera == true)
	{
		mCameraMan->frameRenderingQueued(evt);
	}

	return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool BallkeeperApplication::keyPressed( const OIS::KeyEvent &arg )
{
	if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
	{
		mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	if (arg.key == OIS::KC_C)
		// switch manual camera
	{
		m_bManualCamera = !m_bManualCamera;
	}


	if (m_bManualCamera == true)
	{
		mCameraMan->injectKeyDown(arg);
	}

	return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool BallkeeperApplication::keyReleased( const OIS::KeyEvent &arg )
{
	if (m_bManualCamera == true)
	{
		mCameraMan->injectKeyUp(arg);
	}

	return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool BallkeeperApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	if (m_bManualCamera == true)
	{
		mCameraMan->injectMouseMove(arg);
	}
	return true;
}
bool BallkeeperApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (m_bManualCamera == true)
	{
		mCameraMan->injectMouseDown(arg, id);
	}
	return true;
}
bool BallkeeperApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (m_bManualCamera == true)
	{
		mCameraMan->injectMouseUp(arg, id);
	}
	return true;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BallkeeperApplication::createScene(void)
{
	// Create the common setup of the scene
	//----------------------------------------

	// Sky
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	//mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// Near Infinite plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("BKGPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000.0f, 10000.0f, 10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* pBKGMesh = mSceneMgr->createEntity("BKG", "BKGPlane");
	pBKGMesh->setMaterialName("Examples/CloudySky");

	// Create the Node for the BKG
	Ogre::SceneNode* pBKGNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("BKGNode");
	// Attach the mesh to the node
	pBKGNode->attachObject(pBKGMesh);
	pBKGNode->setPosition(Ogre::Vector3(0.0f, -100.0f, 0.0f));


	// Light
	Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.7f, .7f, .7f));
	directionalLight->setSpecularColour(Ogre::ColourValue(.7f, .7f, .7f));
	directionalLight->setDirection(Ogre::Vector3( 1.f, -1.f, 1.f ));


	// Create text box
	new TextRenderer();
	Ogre::FontManager::getSingletonPtr()->load( "StarWars", "Popular" );


    //Level Name présent dans toute les scènes , on l'attache au panel crée par le constructeur

	int xPosition = mWindow->getWidth()/2;
	int yPosition = 15;
	TextRenderer::getSingleton().addTextBox ("LevelNameA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "20", "StarWars","center");
	xPosition -= 2;
	yPosition -= 2;
	TextRenderer::getSingleton().addTextBox ("LevelNameB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::White, "20", "StarWars","center");

    //Création des textbox de la partie jeux
    TextRenderer::getSingleton().addPanel("PlayPanel");
    xPosition = mWindow->getWidth()/2;
	yPosition = 30;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","TimerBoxA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "50", "StarWars","center");
 	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","TimerBoxB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Red, "50", "StarWars","center");
 	yPosition += 50 ;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","CapturesA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "30", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","CapturesB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Green, "30", "StarWars","center");
	yPosition += 30 ;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","RestantsA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "30", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("PlayPanel","RestantsB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Green, "30", "StarWars","center");

	//Création des textbox de la partie Warm up
    TextRenderer::getSingleton().addPanel("WarmUpPanel");

    xPosition = mWindow->getWidth()/2;
 	yPosition = mWindow->getHeight()/2-20;
 	TextRenderer::getSingleton().addTextBox ("WarmUpPanel","CountdownA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "50", "StarWars","center");
 	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("WarmUpPanel","CountdownB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Red, "50", "StarWars","center");

    //Création des textbox de la partie Cinématique
    TextRenderer::getSingleton().addPanel("CameraWarmUpPanel");

    xPosition = mWindow->getWidth()/2;
	yPosition = 80;
    TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","ObjectifA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "30", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","ObjectifB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::White, "30", "StarWars","center");
	yPosition += 30 ;
	TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","TotalA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "30", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","TotalB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::White, "30", "StarWars","center");

 	yPosition += 50;
 	TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","SkipC", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "16", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("CameraWarmUpPanel","SkipD", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::White, "16", "StarWars","center");

    //Création des textbox de la partie Ecran de fin
    TextRenderer::getSingleton().addPanel("LevelEndPanel");

    xPosition = mWindow->getWidth()/2;
	yPosition = 100;
	TextRenderer::getSingleton().addTextBox ("LevelEndPanel","ResultA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "60", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("LevelEndPanel","ResultB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Red, "60", "StarWars","center");

 	yPosition += 80;
 	TextRenderer::getSingleton().addTextBox ("LevelEndPanel","SkipA", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::Black, "16", "StarWars","center");
	xPosition -= 4;
 	yPosition -= 4;
	TextRenderer::getSingleton().addTextBox ("LevelEndPanel","SkipB", "", xPosition, yPosition, 200, 200, Ogre::ColourValue::White, "16", "StarWars","center");



}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BallkeeperApplication::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	CreateAllLevel();

	// Start the first level
	m_uiCurrentLevel = 0;
	m_apLevel[m_uiCurrentLevel]->Start();
}




//---------------------------------------------------------------------------
// Main app
//---------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        BallkeeperApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
