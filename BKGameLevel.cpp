#include "BKGameLevel.h"
#include "BallkeeperApplication.h"
#include "TextRenderer.h"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKGameLevel::BKGameLevel()
{
	m_pBKApp = NULL;
	m_pLevelNode = NULL;
	m_pTerrain = NULL;
	m_pPlayerBall = NULL;

	m_fLevelDuration = 5.0f;
	m_fLevelTimerPlay = 0.0f;
	m_uiLevelObjective = 1;


	m_v3CamPosition=Ogre::Vector3::ZERO;
	m_v3CamVelocity=Ogre::Vector3::ZERO;
	m_bCinematicFinished=false;
	m_fCamVelocity=80.0f;//vitesse de déplacement caméra pour la cinématique


}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKGameLevel::~BKGameLevel(void)
{
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameLevel::InitLevel(sGameLevel_Init a_sLevelInit, uint a_uiIndex)
{

    m_uiNbOfSheep = a_sLevelInit.m_uiNbOfSheep;
	Ogre::SceneManager*	pSceneMgr = m_pBKApp->GetSceneMgr();

	// Compute a unique name
	Ogre::String strUniqueName =  a_sLevelInit.m_strName;
	strUniqueName += Ogre::StringConverter::toString(a_uiIndex);
	m_strLevelName = strUniqueName;

	// Set level objective
	m_fLevelDuration = a_sLevelInit.m_fLevelDuration;
	m_uiLevelObjective = a_sLevelInit.m_uiLevelObjective;

	// Set up the cam
	Ogre::Camera* pCamera = m_pBKApp->GetCamera();
	pCamera->setPosition(a_sLevelInit.m_v3CamPosition);
	pCamera->setFOVy(Ogre::Degree(a_sLevelInit.m_fCamFov));
	pCamera->lookAt(Ogre::Vector3::ZERO);

	// Create the root node for the level
	Ogre::String strNodeName = strUniqueName;
	strNodeName += "_Node";
	m_pLevelNode = 	pSceneMgr->getRootSceneNode()->createChildSceneNode(strNodeName);
	pSceneMgr->getRootSceneNode()->removeChild(m_pLevelNode);

	// Create the terrain
	m_pTerrain = new BKGameEntity;
	m_pTerrain->SetLevelOwner(this);
	m_pTerrain->InitGameEntityWithPlane(a_sLevelInit.m_sTerrain,0);

	m_v2TerrainSize = a_sLevelInit.m_sTerrain.m_v2Size;//get terrain size

	// Create the player ball
	m_pPlayerBall = new BKPlayerBall;
	m_pPlayerBall->SetLevelOwner(this);
	m_pPlayerBall->InitPlayerBall(a_sLevelInit.m_sPlayer,0);
	m_pPlayerBall->SetStartingPos(a_sLevelInit.m_v3PlayerStartingPos);

	// Create all the sheep ball
	m_vpSheep.reserve(a_sLevelInit.m_uiNbOfSheep);

	BKSheepBall*	pSheepBall = NULL;
	uint uiSheepCount = 0;
	for (uiSheepCount = 0; uiSheepCount < a_sLevelInit.m_uiNbOfSheep; uiSheepCount++)
	{
		pSheepBall = new BKSheepBall;
		pSheepBall->SetLevelOwner(this);
		pSheepBall->InitSheepBall(a_sLevelInit.m_sSheep,uiSheepCount);
		pSheepBall->SetStartingPos(a_sLevelInit.m_av3SheepStartingPos[uiSheepCount]);

		// Add this sheep to the vector
		m_vpSheep.push_back(pSheepBall);
	}


	// Create all the Wolf ball
	m_vpWolf.reserve(a_sLevelInit.m_uiNbOfWolf);

	BKWolfBall*	pWolfBall = NULL;
	uint uiWolfCount = 0;
	for (uiWolfCount = 0; uiWolfCount < a_sLevelInit.m_uiNbOfWolf; uiWolfCount++)
	{
		pWolfBall = new BKWolfBall;
		pWolfBall->SetLevelOwner(this);
		pWolfBall->InitWolfBall(a_sLevelInit.m_sWolf,uiWolfCount);
		pWolfBall->SetStartingPos(a_sLevelInit.m_av3WolfStartingPos[uiWolfCount]);

		// Add this Wolf to the vector
		m_vpWolf.push_back(pWolfBall);
	}

	//Create all the folds
	m_vpFold.reserve(a_sLevelInit.m_uiNbOfFold);

	BKFold* pFold = NULL;
	uint uiFoldCount = 0;
	for (uiFoldCount = 0; uiFoldCount < a_sLevelInit.m_uiNbOfFold; uiFoldCount++)
	{
		pFold = new BKFold;
		pFold->SetLevelOwner(this);
		pFold->InitFold(a_sLevelInit.m_sFold,uiFoldCount);
		pFold->SetStartingPos(a_sLevelInit.m_av3FoldStartingPos[uiFoldCount]);

		// Add this Fold to the vector
		m_vpFold.push_back(pFold);
	}

	m_eLevelState = eLevelState_WarmUp;

}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameLevel::Start()
{
	// Start the level
	//-------------------------
	m_fLevelTimerPlay = 0.0f;
	m_fLevelTimerWarmUp = 0.0f;
	m_itFoldTarget = m_vpFold.begin();
	m_bCinematicFinished=false;
	m_eLevelState = eLevelState_WarmUp;

	Ogre::SceneManager*	pSceneMgr = m_pBKApp->GetSceneMgr();
	pSceneMgr->getRootSceneNode()->addChild(m_pLevelNode);

	// Start all entity
	//-------------------------
	m_pTerrain->Start();
	m_pPlayerBall->Start();

	SheepBallVector::const_iterator Sheep_it;
	for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		pSheepBall->Start();
	}

	WolfBallVector::const_iterator Wolf_it;
	for(Wolf_it = m_vpWolf.begin(); Wolf_it!=m_vpWolf.end(); Wolf_it++)
	{
		BKWolfBall*  pWolfBall = *Wolf_it;
		pWolfBall->Start();
	}


	FoldVector::const_iterator Fold_it;
	for(Fold_it = m_vpFold.begin(); Fold_it!=m_vpFold.end(); Fold_it++)
	{
		BKFold*  pFold = *Fold_it;
		pFold->Start();
	}


	//Camera Starting Pos
	//--------------------

	m_pBKApp->GetCamera()->setPosition(m_pPlayerBall->GetPosition().x,500,m_pPlayerBall->GetPosition().z-400);
	m_pBKApp->GetCamera()->lookAt(m_pPlayerBall->GetPosition());





	// Update the UI
	//-------------------------
	TextRenderer::getSingleton().setText ("LevelNameA",m_strLevelName );
	TextRenderer::getSingleton().setText ("LevelNameB",m_strLevelName );
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameLevel::UpdateWarmUp(const Ogre::FrameEvent& evt)
{

    if(!(m_bCinematicFinished))//Observation du terrain
    {
        UpdateUICameraWarmUp(evt);
        UpdateCameraWarmUp(evt);
    }
    else //countdown avant debut du niveau
    {
        m_fLevelTimerWarmUp += evt.timeSinceLastFrame;
        UpdateUIWarmUp(evt);
        UpdateCameraPlay(evt);
   }

}
void BKGameLevel::UpdatePlay(const Ogre::FrameEvent& evt)
{
	m_fLevelTimerPlay += evt.timeSinceLastFrame;

	//-------------------------
	// Update all entity
	//-------------------------
	m_pTerrain->Update(evt);
	m_pPlayerBall->Update(evt);

	SheepBallVector::const_iterator Sheep_it;
	for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		pSheepBall->Update(evt);
	}

	WolfBallVector::const_iterator Wolf_it;
	for(Wolf_it = m_vpWolf.begin(); Wolf_it!=m_vpWolf.end(); Wolf_it++)
	{
		BKWolfBall*  pWolfBall = *Wolf_it;
		pWolfBall->Update(evt);
	}

	FoldVector::const_iterator Fold_it;
	for(Fold_it = m_vpFold.begin(); Fold_it!=m_vpFold.end(); Fold_it++)
	{
		BKFold*  pFold = *Fold_it;
		pFold->Update(evt);
	}


	// update the camera
	//-------------------------
	if (m_pBKApp->IsManualCameraEnable() == false)
	{
		UpdateCameraPlay(evt);
	}

	// Update the UI
	//-------------------------
	UpdateUIPlay(evt);

}
void BKGameLevel::UpdateLevelEnd(const Ogre::FrameEvent& evt)
{
	UpdateUILevelEnd(evt);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameLevel::Stop()
{
	// Stop all entity
	//-------------------------
	m_pTerrain->Stop();
	m_pPlayerBall->Stop();

	SheepBallVector::const_iterator Sheep_it;
	for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		pSheepBall->Stop();
	}

		WolfBallVector::const_iterator Wolf_it;
	for(Wolf_it = m_vpWolf.begin(); Wolf_it!=m_vpWolf.end(); Wolf_it++)
	{
		BKWolfBall*  pWolfBall = *Wolf_it;
		pWolfBall->Stop();
	}

	FoldVector::const_iterator Fold_it;
	for(Fold_it = m_vpFold.begin(); Fold_it!=m_vpFold.end(); Fold_it++)
	{
		BKFold*  pFold = *Fold_it;
		pFold->Stop();
	}


	// Stop the level
	//-------------------------
	Ogre::SceneManager*	pSceneMgr = m_pBKApp->GetSceneMgr();
	pSceneMgr->getRootSceneNode()->removeChild(m_pLevelNode);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
uint BKGameLevel::GetNbCapturedSheep()
{
	uint  uiSheepCapturedNb=0;

	SheepBallVector::const_iterator Sheep_it;
	for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		if(pSheepBall->GetSheepState() == eSheepState_Captured)
		{
			uiSheepCapturedNb++;
		}
	}
	return uiSheepCapturedNb;
}

uint BKGameLevel::GetNbWanderingSheep()
{
	uint  uiSheepWanderingNb=0;

	SheepBallVector::const_iterator Sheep_it;
	for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		if(pSheepBall->GetSheepState() == eSheepState_Wander)
		{
			uiSheepWanderingNb++;
		}
	}
	return uiSheepWanderingNb;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameLevel::UpdateUIWarmUp(const Ogre::FrameEvent& evt)
{
	float fWarmUpDuration = 5.0f; //a sortir en membre de gamelevel
	float fCountDown = fWarmUpDuration - m_fLevelTimerWarmUp;
	uint uiCountDown = fCountDown+1;



	Ogre::String strReady = "Ready ?";
	Ogre::String strGo = "Go !";
	Ogre::String strTimer = Ogre::StringConverter::toString(uiCountDown-1);

    TextRenderer::getSingleton().showPanel("WarmUpPanel");//affiche container de l'overlay pr le warm up

	if(uiCountDown > 4)//affiche ready pdt une seconde avt countdown warmup
	{
		TextRenderer::getSingleton().setText("CountdownA", strReady );
		TextRenderer::getSingleton().setText("CountdownB", strReady );
	}
	else
	{
		TextRenderer::getSingleton().setText ("CountdownA", strTimer );
		TextRenderer::getSingleton().setText ("CountdownB", strTimer );
	}
    if(uiCountDown <=1)
	{
		TextRenderer::getSingleton().setText ("CountdownA", strGo );
		TextRenderer::getSingleton().setText ("CountdownB", strGo );
	}
	if(uiCountDown <=0)
	{
	    TextRenderer::getSingleton().hidePanel("WarmUpPanel");
		m_eLevelState = eLevelState_Play;//fin du WarmUp
	}
}

void BKGameLevel::UpdateUICameraWarmUp(const Ogre::FrameEvent& evt)
{
	uint uiTotal = m_uiNbOfSheep;

	Ogre::String strObjective = "Nombre de moutons a capturer: ";
    strObjective += Ogre::StringConverter::toString(m_uiLevelObjective);

	Ogre::String strTotal = "Nombre de moutons total: ";
	strTotal	+= Ogre::StringConverter::toString(uiTotal);

    //Update the UI
    TextRenderer::getSingleton().showPanel("CameraWarmUpPanel");

	TextRenderer::getSingleton().setText ("ObjectifA", strObjective );
	TextRenderer::getSingleton().setText ("ObjectifB", strObjective );

	TextRenderer::getSingleton().setText ("TotalA", strTotal );
	TextRenderer::getSingleton().setText ("TotalB", strTotal );

	TextRenderer::getSingleton().setText ("SkipC", Ogre::String("Press back to skip") );
	TextRenderer::getSingleton().setText ("SkipD", Ogre::String("Press back to skip") );


}
void BKGameLevel::UpdateUIPlay(const Ogre::FrameEvent& evt)
{
	float fCountDown = m_fLevelDuration - m_fLevelTimerPlay;
	uint uiCountDown = fCountDown+1.0f;
	uint uiCaptured = GetNbCapturedSheep();
	uint uiWandering = GetNbWanderingSheep();

	Ogre::String strTimer = "Temps: ";
	strTimer += Ogre::StringConverter::toString(uiCountDown);

	Ogre::String strCaptured ="Captures: ";
	strCaptured	+= Ogre::StringConverter::toString(uiCaptured);
	strCaptured += "/";
	strCaptured	+= Ogre::StringConverter::toString(m_uiLevelObjective);

	Ogre::String strWandering = "Restants: ";
	strWandering	+= Ogre::StringConverter::toString(uiWandering);

	// Update the UI
	TextRenderer::getSingleton().showPanel("PlayPanel");

	TextRenderer::getSingleton().setText ("TimerBoxA", strTimer );
	TextRenderer::getSingleton().setText ("TimerBoxB", strTimer );

	TextRenderer::getSingleton().setText ("CapturesA", strCaptured );
	TextRenderer::getSingleton().setText ("CapturesB", strCaptured );

	TextRenderer::getSingleton().setText ("RestantsA", strWandering );
	TextRenderer::getSingleton().setText ("RestantsB", strWandering );

	if(IsFinished())
	{
	    TextRenderer::getSingleton().hidePanel("PlayPanel");
        m_eLevelState = eLevelState_LevelEnd;
	}

}
void BKGameLevel::UpdateUILevelEnd(const Ogre::FrameEvent& evt)
{

    TextRenderer::getSingleton().showPanel("LevelEndPanel");


    if(IsCompleted())
    {
        TextRenderer::getSingleton().setText ("ResultA", Ogre::String("You Win !") );
        TextRenderer::getSingleton().setText ("ResultB", Ogre::String("You Win !") );

        TextRenderer::getSingleton().setText ("SkipA", Ogre::String("Press enter to continue") );
        TextRenderer::getSingleton().setText ("SkipB", Ogre::String("Press enter to continue") );

    }
    else
    {
        TextRenderer::getSingleton().setText ("ResultA", Ogre::String("You Lose !") );
        TextRenderer::getSingleton().setText ("ResultB", Ogre::String("You Lose !") );

        TextRenderer::getSingleton().setText ("SkipA", Ogre::String("Press enter to retry") );
        TextRenderer::getSingleton().setText ("SkipB", Ogre::String("Press enter to retry") );
    }

}


SheepBallVector	BKGameLevel::GetAllSheepAround(BKGameEntity*	a_pGE, float a_fRadius, eSheepState a_eSheepStateWanted)
{
	SheepBallVector  vSheepAround;

	SheepBallVector::const_iterator Sheep_it;
		for(Sheep_it = m_vpSheep.begin(); Sheep_it!=m_vpSheep.end(); Sheep_it++)
		{
			BKSheepBall*  pSheepBall = *Sheep_it;
			if	(	a_pGE->GetPosition().distance( pSheepBall->GetPosition() ) < a_fRadius
				&&	pSheepBall != a_pGE && pSheepBall->GetSheepState() == a_eSheepStateWanted)
			{
				vSheepAround.push_back(pSheepBall);
			}
		}
	return vSheepAround;
}

WolfBallVector	BKGameLevel::GetAllWolfAround(BKGameEntity*	a_pGE, float a_fRadius)
{
	WolfBallVector  vWolfAround;

	WolfBallVector::const_iterator Wolf_it;

		for(Wolf_it = m_vpWolf.begin(); Wolf_it!=m_vpWolf.end(); Wolf_it++)
		{
			BKWolfBall*  pWolfBall = *Wolf_it;
			if	(	a_pGE->GetPosition().distance( pWolfBall->GetPosition() ) < a_fRadius
				&&	pWolfBall != a_pGE)
			{
				vWolfAround.push_back(pWolfBall);
			}
		}
	return vWolfAround;
}

void BKGameLevel::UpdateCameraWarmUp(const Ogre::FrameEvent& evt)
{
    if(m_pBKApp->GetKeyboard()->isKeyDown(OIS::KC_BACK))
    {
        TextRenderer::getSingleton().hidePanel("CameraWarmUpPanel");
        m_bCinematicFinished = true;
        m_itFoldTarget = m_vpFold.begin();
    }
    if(m_itFoldTarget != m_vpFold.end())
    {
        BKFold*  pFoldTarget = *m_itFoldTarget;
        Ogre::Vector3 v3CamTargetWarmUp = Ogre::Vector3(pFoldTarget->GetPosition().x,500.0f,pFoldTarget->GetPosition().z-400.0f);
        Ogre::Vector3 v3CamDirection = v3CamTargetWarmUp - m_pBKApp->GetCamera()->getPosition();
        float fDistanceCamToTarget = v3CamDirection.normalise();

        if( fDistanceCamToTarget > 10.0f)
        {
            m_pBKApp->GetCamera()->setPosition(m_pBKApp->GetCamera()->getPosition() +
                                               v3CamDirection*m_fCamVelocity*evt.timeSinceLastFrame);

            m_pBKApp->GetCamera()->lookAt(pFoldTarget->GetPosition());
        }
        else
        {
            m_itFoldTarget++;
        }

    }
    else
    {
        Ogre::Vector3 v3CamTargetWarmUp = Ogre::Vector3(m_pPlayerBall->GetPosition().x,500.0f,m_pPlayerBall->GetPosition().z-400.0f);
        Ogre::Vector3 v3CamDirection = v3CamTargetWarmUp - m_pBKApp->GetCamera()->getPosition();
        float fDistanceCamToTarget = v3CamDirection.normalise();

        if( fDistanceCamToTarget > 10.0f)
        {
            m_pBKApp->GetCamera()->setPosition(m_pBKApp->GetCamera()->getPosition() +
                                               v3CamDirection*m_fCamVelocity*evt.timeSinceLastFrame);

            m_pBKApp->GetCamera()->lookAt(m_pPlayerBall->GetPosition());
        }
        else
        {
            TextRenderer::getSingleton().hidePanel("CameraWarmUpPanel");
            m_bCinematicFinished = true;
            m_itFoldTarget = m_vpFold.begin();
        }
    }

}
void BKGameLevel::UpdateCameraPlay(const Ogre::FrameEvent& evt)
{
	m_pBKApp->GetCamera()->setPosition(m_pPlayerBall->GetPosition().x,500,m_pPlayerBall->GetPosition().z-400);
	m_pBKApp->GetCamera()->lookAt(m_pPlayerBall->GetPosition());
}
