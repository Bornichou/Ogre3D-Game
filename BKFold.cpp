#include "BKFold.h"
#include "BallkeeperApplication.h"


BKFold::BKFold()
{

}

void BKFold::Update(const Ogre::FrameEvent& evt)
{

	CatchSheep();
	BKGameEntity::Update(evt);
	
}

void BKFold::InitFold(sFoldInit a_sFoldInit, uint a_uiIndex)
{
	m_fFoldRadius = a_sFoldInit.m_fFoldRadius;
	InitGameEntityWithMesh(a_sFoldInit.m_sMesh,a_uiIndex);

	Ogre::String strCircleName = GetUniqueGEName(a_sFoldInit.m_sMesh.m_strName,a_uiIndex);
	strCircleName += "_Circle";
	CreateCircle(m_fFoldRadius,strCircleName,Ogre::ColourValue::White);

}

void BKFold::CatchSheep()
{

	SheepBallVector vSheepDetected;
	SheepBallVector::const_iterator Sheep_it;  

	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_fFoldRadius,eSheepState_Wander);

	for(Sheep_it = vSheepDetected.begin(); Sheep_it != vSheepDetected.end(); Sheep_it++)  
	{  
		BKSheepBall*  pSheepBall = *Sheep_it;
		pSheepBall->CaptureFold(this);
	} 
}