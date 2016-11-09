/*
-----------------------------------------------------------------------------
Filename:    BallkeeperApplication.cpp
-----------------------------------------------------------------------------
*/
#include "BallkeeperApplication.h"
#include "BallKeeperInitDefine.h"

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void BallkeeperApplication::CreateAllLevel(void)
{

	// Create all the level
	uint uiLevelCount;
	for (uiLevelCount = 0; uiLevelCount < BK_LEVEL_NB; uiLevelCount++)
	{
		m_apLevel[uiLevelCount] = new BKGameLevel();
		m_apLevel[uiLevelCount]->SetApplicationOwner(this);
		m_apLevel[uiLevelCount]->InitLevel(g_asBallKeeperInit[uiLevelCount],uiLevelCount);
	}

}

