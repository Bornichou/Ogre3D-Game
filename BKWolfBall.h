#ifndef __BKWolfBall_h_
#define __BKWolfBall_h_

#include "BaseApplication.h"
#include "BKBall.h"

enum eWolfState
{
	eWolfState_Wander = 0,
	eWolfState_Flee, 
	eWolfState_Hunt,

	eWolfState_Nb
};


//---------------------------------------------------------------------------
// class BKBall
//---------------------------------------------------------------------------
class BKWolfBall: public BKBall
{
public:
	BKWolfBall();

	void InitWolfBall(sWolfBallInit a_sWolfBallInit, uint a_uiIndex);
	eWolfState GetWolfState(){return m_eWolfState;}
	
	// virtual from GE
	virtual void Update(const Ogre::FrameEvent& evt);

	// virtual from Ball
	virtual void UpdateSteering(const Ogre::FrameEvent& evt);

	virtual void UpdatePosAndRot(const Ogre::FrameEvent& evt);
	
	//virtual from GameEntity
	virtual void Start(void);
	void KillSheep(void);

protected:

	eWolfState		m_eWolfState;

	BKSheepBall*    m_pSheepTarget;

	sFlockingParam	m_sInterceptionParam;
	sFlockingParam	m_sSeparationParam;
	Ogre::ManualObject* m_pManualCircle;

	float	m_fKillRadius;


};

#endif // #ifndef __BKWolfBall_h_
