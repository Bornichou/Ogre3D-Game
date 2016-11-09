#include "BKPlayerBall.h"
#include "BallkeeperApplication.h"

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
BKPlayerBall::BKPlayerBall()
{
	m_fPlayerTargetSpeed = 500.0f;
	m_fPlayerForceRatio = 100.0f; 

}
//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void BKPlayerBall::InitPlayerBall(sPlayerBallInit a_sPlayerBallInit, uint a_uiIndex)
{
	m_fPlayerTargetSpeed = a_sPlayerBallInit.m_fPlayerTargetSpeed;
	m_fPlayerForceRatio = a_sPlayerBallInit.m_fPlayerForceRatio;	

	InitBall(a_sPlayerBallInit.m_sBall,a_uiIndex);
}

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void BKPlayerBall::UpdateSteering(const Ogre::FrameEvent& evt)
{
	OIS::Keyboard* pKeyboard = m_pLevel->GetBKApp()->GetKeyboard();
	Ogre::Vector3 v3transvector=Ogre::Vector3::ZERO; //vecteur translation

	if(pKeyboard->isKeyDown(OIS::KC_UP) || pKeyboard->isKeyDown(OIS::KC_W))
	{
		v3transvector.z += 1;
	}
	if(pKeyboard->isKeyDown(OIS::KC_DOWN) || pKeyboard->isKeyDown(OIS::KC_S))
	{
		v3transvector.z -= 1;
	}
	if(pKeyboard->isKeyDown(OIS::KC_LEFT) || pKeyboard->isKeyDown(OIS::KC_A))
	{
		v3transvector.x += 1;
	}
	if(pKeyboard->isKeyDown(OIS::KC_RIGHT) || pKeyboard->isKeyDown(OIS::KC_D))
	{
		v3transvector.x -= 1;
	}
	if(v3transvector  != Ogre::Vector3::ZERO)//pour éviter division par zéro
	{
		v3transvector.normalise();//normalise le vecteur
	}
	v3transvector*=m_fPlayerTargetSpeed;//multiplie par la vitesse désirée
	m_v3CurrentSteering=v3transvector - m_v3Velocity;//calcule nouveau steering
	m_v3CurrentSteering*=m_fPlayerForceRatio;//le module par le force ratio

}
