#ifndef __BKBall_h_
#define __BKBall_h_

#include "BaseApplication.h"
#include "BKGameEntity.h"


//---------------------------------------------------------------------------
// class BKBall
//---------------------------------------------------------------------------
class BKBall: public BKGameEntity
{
public:
	BKBall();
	
	void InitBall(sBallInit a_sBallInit, uint a_uiIndex);

	// virtual from GameEntity
	virtual void Start();
	virtual void Stop();
    virtual void UpdatePosAndRot(const Ogre::FrameEvent& evt);

	// virtual from Ball
	virtual void UpdateSteering(const Ogre::FrameEvent& evt);

	Ogre::Vector3	SteeringFlee(Ogre::Vector3	a_v3PosToFlee, float a_fForceRatio);
	Ogre::Vector3	SteeringSeek(Ogre::Vector3	a_v3PosToSeek, float a_fSeekSpeed);
	//Ogre::Vector3	SteeringIntercept(Ogre::Vector3	a_v3PosToSeek, float a_fSeekSpeed);
	Ogre::Vector3	SteeringArrival(Ogre::Vector3	a_v3PosToSeek, float a_fSeekSpeed, float a_fSlowingDist);

protected:

	Ogre::Vector3 ComputeSpeedTo(Ogre::Vector3	a_v3PosToReach, float a_fSpeed);

	// Current var
	Ogre::Vector3 m_v3CurrentSteering;
	Ogre::Vector3 m_v3Velocity;

	// Ball setup
	float m_fMass;
	float m_fMaxForce;
	float m_fMaxSpeed;

	//collision param
	float m_fCollisionDelta;

	
};

#endif // #ifndef __BKBall_h_
