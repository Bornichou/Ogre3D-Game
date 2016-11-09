#ifndef __BKGameEntity_h_
#define __BKGameEntity_h_

#include "BaseApplication.h"
#include "BallKeeperTypeDef.h"
#include "BallKeeperInitStructDefine.h"

class BKGameLevel;

//---------------------------------------------------------------------------
// class BKGameEntity
//---------------------------------------------------------------------------
class BKGameEntity
{
public:
	BKGameEntity();
	virtual ~BKGameEntity(void);

	void SetLevelOwner(BKGameLevel* a_pLevel) { m_pLevel = a_pLevel;}

	void InitGameEntityWithMesh(sGameEntityMeshInit a_sGEMeshInit, uint a_uiIndex);
	void InitGameEntityWithPlane(sGameEntityPlaneInit a_sGEPlaneInit, uint a_uiIndex);

	void SetStartingPos(Ogre::Vector3 a_v3StartingPos);

	virtual void Start();
	virtual void Update(const Ogre::FrameEvent& evt);
	virtual void Stop();

	virtual void UpdatePosAndRot(const Ogre::FrameEvent& evt);

	Ogre::Vector3 GetPosition() { return m_v3Position; }

protected:
	Ogre::String  GetUniqueGEName(Ogre::String a_strName,uint a_uiIndex);

	Ogre::ManualObject* CreateCircle(float a_fRadius, Ogre::String a_strUniqueName, Ogre::ColourValue a_rColor);

	// Owner
	BKGameLevel*		m_pLevel;

	// Starting position
	Ogre::Vector3		m_v3StartingPosition;

	// Current position & At
	Ogre::Vector3		m_v3Position;
	Ogre::Vector3		m_v3AtOrientation;

	// Node & Mesh
	Ogre::SceneNode*	m_pNode;
	Ogre::SceneNode*	m_pDecalNode;
	Ogre::Entity*		m_pMesh;
};

#endif // #ifndef __BKGameEntity_h_
