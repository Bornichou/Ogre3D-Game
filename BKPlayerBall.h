#ifndef __BKPlayerBall_h_
#define __BKPlayerBall_h_

#include "BaseApplication.h"
#include "BKBall.h"

//---------------------------------------------------------------------------
// class BKBall
//---------------------------------------------------------------------------
class BKPlayerBall: public BKBall
{
public:
	BKPlayerBall();

	void InitPlayerBall(sPlayerBallInit a_sPlayerBallInit, uint a_uiIndex);

	// virtual from Ball
	virtual void UpdateSteering(const Ogre::FrameEvent& evt);

protected:

	float	m_fPlayerTargetSpeed;
	float	m_fPlayerForceRatio;

};

#endif // #ifndef __BKPlayerBall_h_
