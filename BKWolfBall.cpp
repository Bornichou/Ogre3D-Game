#include "BKWolfBall.h"
#include "BallkeeperApplication.h"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKWolfBall::BKWolfBall()
{
	m_eWolfState = eWolfState_Wander;
	m_fMaxForce = 10000.0f;
	m_fMaxSpeed = 1000.0f;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKWolfBall::InitWolfBall(sWolfBallInit a_sWolfBallInit, uint a_uiIndex)
{
	m_sInterceptionParam = a_sWolfBallInit.m_sInterceptionParam;
	m_sSeparationParam = a_sWolfBallInit.m_sSeparationParam;
	m_fKillRadius = a_sWolfBallInit.m_fKillRadius;

	InitBall(a_sWolfBallInit.m_sBall,a_uiIndex);

	m_pDecalNode->yaw(Ogre::Radian(-Ogre::Math::PI / 2.0f));

	Ogre::String strCircleName = GetUniqueGEName(a_sWolfBallInit.m_sBall.m_sMesh.m_strName,a_uiIndex);
	strCircleName += "_Circle";
	m_pManualCircle = CreateCircle(m_sInterceptionParam.m_fRadius,strCircleName,Ogre::ColourValue::Red);
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------


void BKWolfBall::Start()
{
    m_pManualCircle->setVisible(true);
	m_eWolfState = eWolfState_Wander;
	m_pSheepTarget = NULL;
	BKBall::Start();
}

void BKWolfBall::KillSheep()
{

	SheepBallVector vSheepDetected;
	SheepBallVector::const_iterator Sheep_it;

	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_fKillRadius,eSheepState_Wander);

	for(Sheep_it = vSheepDetected.begin(); Sheep_it != vSheepDetected.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		pSheepBall->Kill();
	}
}

void BKWolfBall::Update(const Ogre::FrameEvent& evt)
{
	BKBall::Update(evt);

	KillSheep();
}
void BKWolfBall::UpdatePosAndRot(const Ogre::FrameEvent& evt)
{
	m_fCollisionDelta = 10.0f;
	BKBall::UpdatePosAndRot(evt);

	//collision avec les enclos
	FoldVector  vFoldAround = m_pLevel->GetAllFold();

	FoldVector::const_iterator Fold_it;

	for(Fold_it = vFoldAround.begin(); Fold_it!=vFoldAround.end(); Fold_it++)
	{
		BKFold*  pFold = *Fold_it;
		Ogre::Vector3 v3DistToCenterOfField = pFold->GetPosition()-m_v3Position;
		float fDistToFold = v3DistToCenterOfField.normalise();

		if(fDistToFold < pFold->GetFoldRadius())//if wolf inside the circle
		{
			m_v3Position += v3DistToCenterOfField * (fDistToFold - pFold->GetFoldRadius());
			//m_v3Velocity = -m_v3Velocity;
		}
	}
}

void BKWolfBall::UpdateSteering(const Ogre::FrameEvent& evt)
{
	Ogre::Vector3 v3DesiredVelocity = Ogre::Vector3::ZERO;



	// Interception

	SheepBallVector vSheepDetected;
	SheepBallVector::const_iterator Sheep_it;
	vSheepDetected = m_pLevel->GetAllSheepAround(this,m_sInterceptionParam.m_fRadius,eSheepState_Wander);//Cherche tous les moutons
																										//dans le rayon d attrapage

	Ogre::Vector3 v3InterceptionSteering = Ogre::Vector3::ZERO;
	float fMinDistToSheep = m_sInterceptionParam.m_fRadius + 10.0;
	m_pSheepTarget = NULL; //Mouton cible du Loup

	for (Sheep_it = vSheepDetected.begin(); Sheep_it!=vSheepDetected.end(); Sheep_it++)
	{
		BKSheepBall*  pSheepBall = *Sheep_it;
		if(fMinDistToSheep >(pSheepBall->GetPosition()-GetPosition()).normalise())//si distance mouton plus proche que distance avant
		{
			fMinDistToSheep = (pSheepBall->GetPosition()-GetPosition()).normalise();
			m_pSheepTarget = *Sheep_it;
		}
	}

	Ogre::Vector3 v3PosAngle;
	if(m_pSheepTarget != NULL)//si on a une cible
	{
		v3InterceptionSteering = SteeringSeek(m_pSheepTarget->GetPosition(),m_fMaxSpeed);
		m_eWolfState = eWolfState_Hunt;
	}
	else
	{
		m_eWolfState = eWolfState_Wander;
	}

    //Separation
	Ogre::Vector3 v3SeparationSteering = Ogre::Vector3::ZERO;
	WolfBallVector vWolfDetected;
	WolfBallVector::const_iterator Wolf_it;
	vWolfDetected = m_pLevel->GetAllWolfAround(this,m_sSeparationParam.m_fRadius);

	for(Wolf_it = vWolfDetected.begin(); Wolf_it!=vWolfDetected.end(); Wolf_it++)
	{
		BKWolfBall*  pWolfBall = *Wolf_it;
		Ogre::Vector3 v3CurSeparationSteering =  m_v3Position - pWolfBall->GetPosition();

		float fDist = v3CurSeparationSteering.normalise();
		v3CurSeparationSteering *=  (m_sSeparationParam.m_fRadius - fDist) / m_sSeparationParam.m_fRadius;

		v3SeparationSteering += v3CurSeparationSteering*m_sSeparationParam.m_fWeight;
	}



	//Target

	Ogre::Vector3 v3SteeringTarget = Ogre::Vector3::ZERO;
	float fSteeringTargetWeight = 5.0f;
    v3SteeringTarget = -m_v3Velocity;







	if(m_eWolfState == eWolfState_Hunt)
	{
	    m_pManualCircle->setVisible(false);
		m_v3CurrentSteering = m_sInterceptionParam.m_fWeight*v3InterceptionSteering +
							  m_sSeparationParam.m_fWeight*v3SeparationSteering +
							  fSteeringTargetWeight*v3SteeringTarget;

	}
	//else if(m_eWolfState = eWolfState_Flee)
	//{
	//	m_v3CurrentSteering = fSteeringTargetWeight*v3SteeringTarget;
	//}
	else
	{
		m_pManualCircle->setVisible(true);
		m_v3CurrentSteering = v3SteeringTarget*fSteeringTargetWeight;
	}
}
