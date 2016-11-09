#ifndef __BKGameLevel_h_
#define __BKGameLevel_h_

#include "BaseApplication.h"
#include <OgrePlane.h>
#include <OgreMeshManager.h>
#include "BallKeeperTypeDef.h"
#include "BKGameEntity.h"
#include "BKPlayerBall.h"
#include "BKSheepBall.h"
#include "BKFold.h"
#include "BKWolfBall.h"
#include "BallKeeperInitStructDefine.h"

class BallkeeperApplication;

enum eLevelState
{
	eLevelState_WarmUp = 0,
	eLevelState_Play,
	eLevelState_LevelEnd,

	eLevelState_Nb
};


//---------------------------------------------------------------------------
// class BKGameLevel
//---------------------------------------------------------------------------
class BKGameLevel
{
public:
	BKGameLevel();
	virtual ~BKGameLevel(void);

	void InitLevel(sGameLevel_Init a_sLevelInit, uint a_uiIndex);

	void Start();
	void UpdatePlay(const Ogre::FrameEvent& evt);
	void UpdateWarmUp(const Ogre::FrameEvent& evt);
	void UpdateLevelEnd(const Ogre::FrameEvent& evt);

	void Stop();

	void SetApplicationOwner(BallkeeperApplication* a_pBKApp) { m_pBKApp = a_pBKApp; }

	Ogre::SceneNode*		GetLevelNode() { return m_pLevelNode;	}
	BallkeeperApplication*	GetBKApp() { return m_pBKApp;	}
	Ogre::String			GetLevelName() { return m_strLevelName;	}
	eLevelState				GetLeveState(){return m_eLevelState;}

	uint					GetNbCapturedSheep();
	uint					GetNbWanderingSheep();
	bool					IsFinished() { return (m_fLevelTimerPlay >= m_fLevelDuration)||(GetNbWanderingSheep() == 0)
													||(GetNbWanderingSheep()+GetNbCapturedSheep() < m_uiLevelObjective);	}

	bool					IsCompleted() { return GetNbCapturedSheep() >= m_uiLevelObjective;	}

	BKPlayerBall*			GetPlayerBall() { return m_pPlayerBall;	}

	Ogre::Vector2           GetTerrainSize() { return m_v2TerrainSize; }

	WolfBallVector			GetAllWolfAround(BKGameEntity*	a_pGE, float a_fRadius);

	SheepBallVector			GetAllSheepAround(BKGameEntity*	a_pGE, float a_fRadius, eSheepState a_eSheepStateWanted);
	FoldVector              GetAllFold(){return m_vpFold;};

protected:

	void UpdateUIWarmUp(const Ogre::FrameEvent& evt);
	void UpdateUICameraWarmUp(const Ogre::FrameEvent& evt);
	void UpdateUIPlay(const Ogre::FrameEvent& evt);
	void UpdateUILevelEnd(const Ogre::FrameEvent& evt);
	void UpdateCameraWarmUp(const Ogre::FrameEvent& evt);
	void UpdateCameraPlay(const Ogre::FrameEvent& evt);

	// Level Name
	Ogre::String			m_strLevelName;

	//Level State
	eLevelState				m_eLevelState;

	// Pointer to the app
	BallkeeperApplication*	m_pBKApp;
	Ogre::SceneNode*		m_pLevelNode;

	// Level objective
	float					m_fLevelDuration;
	float					m_fLevelTimerPlay;
	float                   m_fLevelTimerWarmUp;
	uint					m_uiLevelObjective;
	uint					m_uiNbOfSheep;

	// Level content
	BKGameEntity*				m_pTerrain;
	Ogre::Vector2               m_v2TerrainSize;

	BKPlayerBall*				m_pPlayerBall;
	SheepBallVector				m_vpSheep;
	std::vector<BKWolfBall*>			m_vpWolf;
 	std::vector<BKFold*>				m_vpFold;

 	FoldVector::const_iterator   m_itFoldTarget;

	//Caméra
	Ogre::Vector3 m_v3CamPosition;
	Ogre::Vector3 m_v3CamVelocity;
	bool          m_bCinematicFinished;
	float         m_fCamVelocity;
};

#endif // #ifndef __BKGameLevel_h_
