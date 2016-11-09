#include "BKBall.h"
#include "BKGameLevel.h"
#define BK_MIN_SPEED_TO_TURN 10.0f

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKBall::BKBall()
{
	// Current var
	m_v3CurrentSteering = Ogre::Vector3::ZERO;
	m_v3Velocity = Ogre::Vector3::ZERO;

	// Ball setup
	m_fMass = 1.0f;
	m_fMaxForce = 10000.0f;
	m_fMaxSpeed = 1000.0f;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKBall::InitBall(sBallInit a_sBallInit, uint a_uiIndex)
{
	// Ball setup
	m_fMass = a_sBallInit.m_fMass;
	m_fMaxForce = a_sBallInit.m_fMaxForce;
	m_fMaxSpeed = a_sBallInit.m_fMaxSpeed;
	m_fCollisionDelta = 0;

	InitGameEntityWithMesh(a_sBallInit.m_sMesh,a_uiIndex);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKBall::Start()
{
	BKGameEntity::Start();

	// Set a random At direction
	float fXrand = 5 - rand()%10;
	float fZrand = 5 - rand()%10;
	m_v3AtOrientation = Ogre::Vector3(fXrand,0,fZrand);
	m_v3AtOrientation.normalise();

	m_v3CurrentSteering = Ogre::Vector3::ZERO;
	m_v3Velocity = Ogre::Vector3::ZERO;

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKBall::Stop()
{
	BKGameEntity::Stop();
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKBall::UpdatePosAndRot(const Ogre::FrameEvent& evt)
{
	// Reset current steering
	m_v3CurrentSteering = Ogre::Vector3::ZERO;

	// Update the steering for this frame
	UpdateSteering(evt);

	// steering_force = truncate (steering_direction, max_force)
	Ogre::Vector3 v3SteeringForce = m_v3CurrentSteering;
	float fSteeringLength = v3SteeringForce.length();
	if (fSteeringLength > m_fMaxForce)
	{
		v3SteeringForce *= m_fMaxForce/fSteeringLength;
	}

	// acceleration = steering_force / mass
	Ogre::Vector3 v3Acceleration = v3SteeringForce / m_fMass;

	// velocity = truncate (velocity + acceleration, max_speed)
	m_v3Velocity += v3Acceleration * evt.timeSinceLastFrame;
	float fVelocityLength = m_v3Velocity.length();
	if (fVelocityLength > m_fMaxSpeed)
	{
		m_v3Velocity *= m_fMaxSpeed/fVelocityLength;
	}

	// position = position + velocity
	m_v3Position += m_v3Velocity * evt.timeSinceLastFrame;

	// At Orientation is equal to the direction of the velocity
	// (if too low keep the same direction)
	if (fVelocityLength > BK_MIN_SPEED_TO_TURN)
	{
		m_v3AtOrientation = m_v3Velocity;
	}


	//check si sort not terrain (Collision with the bord)
	if( abs(m_v3Position.x) > (m_pLevel->GetTerrainSize().x / 2) - m_fCollisionDelta
		|| abs(m_v3Position.z) > (m_pLevel->GetTerrainSize().y / 2) - m_fCollisionDelta)

	{

		if(abs(m_v3Position.x) > (m_pLevel->GetTerrainSize().x / 2) - m_fCollisionDelta)
		{
			if(m_v3Position.x < 0)
			{
				m_v3Position.x = -(m_pLevel->GetTerrainSize().x / 2) + m_fCollisionDelta;
				m_v3Velocity.x = 0;

			}
			else
			{
				m_v3Position.x = (m_pLevel->GetTerrainSize().x / 2) - m_fCollisionDelta;
				m_v3Velocity.x = 0;
			}

		}

		if(abs(m_v3Position.z) > (m_pLevel->GetTerrainSize().y / 2) - m_fCollisionDelta)
		{
			if(m_v3Position.z < 0)
			{
				m_v3Position.z = -(m_pLevel->GetTerrainSize().y / 2) + m_fCollisionDelta;
				m_v3Velocity.z = 0;
			}
			else
			{
				m_v3Position.z = (m_pLevel->GetTerrainSize().y / 2) -m_fCollisionDelta;
				m_v3Velocity.z = 0;
			}
		}
	}

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKBall::UpdateSteering(const Ogre::FrameEvent& evt)
{

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::Vector3 BKBall::ComputeSpeedTo(Ogre::Vector3	a_v3PosToReach, float a_fSpeed)
{
	Ogre::Vector3 v3DesiredVelocity = a_v3PosToReach - m_v3Position;

	if	(v3DesiredVelocity.length() < 0.001f)
	{
		if	(m_v3Velocity.length() < 0.001f)
		{
			v3DesiredVelocity = Ogre::Vector3::UNIT_X;
		}
		else
		{
			v3DesiredVelocity = m_v3Velocity;
		}
	}

	v3DesiredVelocity.normalise();
	v3DesiredVelocity *= a_fSpeed;

	return v3DesiredVelocity;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::Vector3 BKBall::SteeringSeek(Ogre::Vector3	a_v3PosToSeek, float a_fSeekSpeed)
{
	Ogre::Vector3 v3DesiredVelocity = ComputeSpeedTo(a_v3PosToSeek, a_fSeekSpeed);
	Ogre::Vector3 v3SeekSteering = v3DesiredVelocity - m_v3Velocity;
	return v3SeekSteering;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::Vector3 BKBall::SteeringFlee(Ogre::Vector3	a_v3PosToFlee, float a_fFleeSpeed)
{
	return -SteeringSeek(a_v3PosToFlee,a_fFleeSpeed);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::Vector3 BKBall::SteeringArrival(Ogre::Vector3	a_v3PosToSeek, float a_fSeekSpeed, float a_fSlowingDist)
{
	Ogre::Vector3 v3SpeedTo = ComputeSpeedTo(a_v3PosToSeek,1.0f);

	float fRampedSpeed = a_fSeekSpeed * (m_v3Position.distance(a_v3PosToSeek) / a_fSlowingDist);
	float fClampedSpeed = a_fSeekSpeed;
	if	(fRampedSpeed < fClampedSpeed)
	{
		fClampedSpeed = fRampedSpeed;
	}

	v3SpeedTo *= fClampedSpeed;

	Ogre::Vector3 v3SeekSteering = v3SpeedTo - m_v3Velocity;

	return v3SeekSteering;
}
