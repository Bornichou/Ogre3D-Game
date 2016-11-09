#ifndef __BKFold_h_
#define __BKFold_h_

#include "BaseApplication.h"
#include "BKGameEntity.h"

//---------------------------------------------------------------------------
// class BKFold
//---------------------------------------------------------------------------
class BKFold: public BKGameEntity
{
public:
	BKFold();

	

	virtual void Update(const Ogre::FrameEvent& evt);
	void InitFold(sFoldInit a_sFoldInit, uint a_uiIndex);
	float GetFoldRadius(void){return m_fFoldRadius;}
	void CatchSheep(void);

protected:

	float	m_fFoldRadius;

};


#endif // #ifndef __BKFold_h_