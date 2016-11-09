/*
-----------------------------------------------------------------------------
Filename:    BallkeeperApplication.h
-----------------------------------------------------------------------------
*/
#ifndef __BallkeeperApplication_h_
#define __BallkeeperApplication_h_

#include "BaseApplication.h"
#include "BallKeeperTypeDef.h"
#include "BKGameLevel.h"

#define BK_LEVEL_NB	5

//---------------------------------------------------------------------------
// class BallkeeperApplication
//---------------------------------------------------------------------------
class BallkeeperApplication : public BaseApplication
{
public:
    BallkeeperApplication(void);
    virtual ~BallkeeperApplication(void);

	OIS::Keyboard*			GetKeyboard() { return mKeyboard; }
	Ogre::SceneManager*		GetSceneMgr() { return mSceneMgr; }
	Ogre::Camera*			GetCamera()	{ return mCamera; }
	bool					IsManualCameraEnable()	{ return m_bManualCamera; }

protected:

	// BaseAplication
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
    virtual void createScene(void);
    virtual void createFrameListener(void);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// OIS::KeyListener
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	// OIS::MouseListener
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	// Levels
	void CreateAllLevel(void);

	uint			m_uiCurrentLevel;
	BKGameLevel*	m_apLevel[BK_LEVEL_NB];

	// Manual Camera control
	bool			m_bManualCamera;
};

#endif // #ifndef __BallkeeperApplication_h_
