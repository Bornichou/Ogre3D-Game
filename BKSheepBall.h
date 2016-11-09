#ifndef __BKSheepBall_h_
#define __BKSheepBall_h_

#include "BaseApplication.h"
#include "BKBall.h"

enum eSheepState
{
	eSheepState_Wander = 0,
	eSheepState_Flee, 
	eSheepState_Captured,
	eSheepState_Dead,

	eSheepState_Nb
};


//---------------------------------------------------------------------------
// class BKBall
//---------------------------------------------------------------------------
class BKSheepBall: public BKBall
{
public:
	BKSheepBall();

	void InitSheepBall(sSheepBallInit a_sSheepBallInit, uint a_uiIndex);
	void CaptureFold(BKFold* a_pCaptureFold);
	eSheepState GetSheepState(){return m_eSheepState;}
	void Kill();
	

	// virtual from Ball
	virtual void UpdateSteering(const Ogre::FrameEvent& evt);
	
	virtual void UpdatePosAndRot(const Ogre::FrameEvent& evt);

	//virtual from GameEntity
	virtual void Start(void);

protected:

	eSheepState		m_eSheepState;

	BKFold*         m_pCaptureFold;

	sFlockingParam	m_sCohesionParam;
	sFlockingParam	m_sSeparationParam;
	sFlockingParam	m_sAlignementParam;
	sFlockingParam	m_sSeparationWolfParam;


};

#endif // #ifndef __BKSheepBall_h_
