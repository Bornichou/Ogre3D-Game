#include "BKSheepBall.h"
#include "BallkeeperApplication.h"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKSheepBall::BKSheepBall()
{
	m_eSheepState = eSheepState_Wander;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKSheepBall::InitSheepBall(sSheepBallInit a_sSheepBallInit, uint a_uiIndex)
{
	m_sCohesionParam = a_sSheepBallInit.m_sCohesionParam;
	m_sSeparationParam = a_sSheepBallInit.m_sSeparationParam;
	m_sAlignementParam = a_sSheepBallInit.m_sAlignementParam;
	m_sSeparationWolfParam = a_sSheepBallInit.m_sSeparationWolfParam;

	InitBall(a_sSheepBallInit.m_sBall,a_uiIndex);
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

void BKSheepBall::CaptureFold(BKFold* a_pCaptureFold)
{
	m_pCaptureFold = a_pCaptureFold;
	m_eSheepState = eSheepState_Captured;
}

void BKSheepBall::Kill()
{
	m_eSheepState=eSheepState_Dead;
	m_v3Velocity = 0;
	m_pNode->setVisible(false);
	//m_pNode->detachAllObjects();
	//m_pNode->attachObject(m_pMeshDead);
}

void BKSheepBall::Start()
{
	m_eSheepState = eSheepState_Wander;
	m_pCaptureFold = NULL;
	m_pNode->setVisible(true);
	BKBall::Start();
}

void BKSheepBall::UpdateSteering(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 v3DesiredVelocity = Ogre::Vector3::ZERO;



	SheepBallVector vSheepDetected;
	SheepBallVector::const_iterator Sheep_it;

	// Separation

	Ogre::Vector3 v3SeparationSteering = Ogre::Vector3::ZERO;
	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_sSeparationParam.m_fRadius,eSheepState_Wander);

	for(Sheep_it = vSheepDetected.begin(); Sheep_it!=vSheepDetected.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		Ogre::Vector3 v3CurSeparationSteering =  m_v3Position - pSheepBall->GetPosition();

		float fDist = v3CurSeparationSteering.normalise();
		v3CurSeparationSteering *=  (m_sSeparationParam.m_fRadius - fDist) / m_sSeparationParam.m_fRadius;

		v3SeparationSteering += v3CurSeparationSteering*m_sSeparationParam.m_fWeight;
	}



	// Cohesion

	vSheepDetected.clear();
	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_sCohesionParam.m_fRadius,eSheepState_Wander);
	Ogre::Vector3 v3Barycenter = Ogre::Vector3::ZERO;
	Ogre::Vector3 v3CohesionSteering = Ogre::Vector3::ZERO;

	for (Sheep_it = vSheepDetected.begin(); Sheep_it!=vSheepDetected.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		v3Barycenter += pSheepBall->GetPosition() ;
	}
	if(vSheepDetected.size()!=0)
	{
		v3Barycenter = v3Barycenter / vSheepDetected.size();
		v3CohesionSteering = SteeringSeek(v3Barycenter,m_fMaxSpeed);
	}

	// Alignement
	// Moyenne des vitesses des voisins
	// puis steering = vitesse moyenne - vit actu
	vSheepDetected.clear();
	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_sCohesionParam.m_fRadius,eSheepState_Wander);
	Ogre::Vector3 v3Mean = Ogre::Vector3::ZERO;
	Ogre::Vector3 v3AlignementSteering = Ogre::Vector3::ZERO;

	for (Sheep_it = vSheepDetected.begin(); Sheep_it!=vSheepDetected.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		v3Mean += pSheepBall->m_v3Velocity ;
	}
	if(vSheepDetected.size()!=0)
	{
		v3Mean = v3Mean / vSheepDetected.size();
		v3AlignementSteering = v3Mean - m_v3Velocity;
	}

	//Target

	Ogre::Vector3 v3SteeringTarget = Ogre::Vector3::ZERO;
	float fSteeringTargetWeight = 5.0f;


	Ogre::Vector3 v3DistToPlayer = (m_v3Position - m_pLevel->GetPlayerBall()->GetPosition());
	float fDistToPlayer = v3DistToPlayer.normalise();
	float fFleePlayerRadius = 50.0f;
	float fFleePlayerWeight = 80.0f;


	if(fDistToPlayer<fFleePlayerRadius)
	{
		v3SteeringTarget = fFleePlayerWeight*SteeringFlee(m_pLevel->GetPlayerBall()->GetPosition(),m_fMaxForce);
	}
	else
	{
		v3SteeringTarget = 0 - m_v3Velocity;
	}



	// Separation pour flee des Wolf

	WolfBallVector vWolfDetected;
	WolfBallVector::const_iterator Wolf_it;


	Ogre::Vector3 v3SeparationWolfSteering = Ogre::Vector3::ZERO;
	vWolfDetected = m_pLevel->GetAllWolfAround(this,m_sSeparationWolfParam.m_fRadius);

	for(Wolf_it = vWolfDetected.begin(); Wolf_it!=vWolfDetected.end(); Wolf_it++)
	{
		BKWolfBall*  pWolfBall = *Wolf_it;
		Ogre::Vector3 v3CurSeparationWolfSteering =  m_v3Position - pWolfBall->GetPosition();

		float fDist = v3CurSeparationWolfSteering.normalise();
		v3CurSeparationWolfSteering *=  (m_sSeparationWolfParam.m_fRadius - fDist) / m_sSeparationWolfParam.m_fRadius;

		v3SeparationWolfSteering += v3CurSeparationWolfSteering;
	}
	v3SeparationWolfSteering.normalise();//normalise vecteur (on ne veut pas que s'il y a plusieurs wolfs le sheep fuit plus vite




	if(m_eSheepState == eSheepState_Dead)
	{
		m_v3CurrentSteering = -m_v3Velocity;
	}
	else if(m_eSheepState != eSheepState_Captured)
	{
		m_v3CurrentSteering = m_sSeparationParam.m_fWeight*v3SeparationSteering +
							  m_sCohesionParam.m_fWeight*v3CohesionSteering +
							  m_sAlignementParam.m_fWeight*v3AlignementSteering +
							  fSteeringTargetWeight*v3SteeringTarget +
							  m_sSeparationWolfParam.m_fWeight*v3SeparationWolfSteering;
	}
	else
	{
		m_v3CurrentSteering = SteeringArrival(m_pCaptureFold->GetPosition(),m_fMaxSpeed,m_pCaptureFold->GetFoldRadius());
	}
}




//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKSheepBall::UpdatePosAndRot(const Ogre::FrameEvent& evt)
{
	m_fCollisionDelta = 10.0f;
	BKBall::UpdatePosAndRot(evt);

	if(m_pCaptureFold != NULL)//si capturé => collision avec fold
	{
		Ogre::Vector3 v3DistToCenterOfField = m_pCaptureFold->GetPosition()-m_v3Position;
		float fDistToFold = v3DistToCenterOfField.normalise();

		if(fDistToFold > m_pCaptureFold->GetFoldRadius())//if sheep en dehors circle
		{
			m_v3Position += v3DistToCenterOfField * (fDistToFold - m_pCaptureFold->GetFoldRadius());
			m_v3Velocity = -m_v3Velocity;
		}
	}
}
