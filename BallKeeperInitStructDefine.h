/*
-----------------------------------------------------------------------------
Filename:    BallkeeperInitStructDefine.h
-----------------------------------------------------------------------------
*/
#ifndef __BallkeeperInitStructDefine_h_
#define __BallkeeperInitStructDefine_h_

//---------------------------------------------------------------------------
// STEERING
//---------------------------------------------------------------------------
struct sFlockingParam
{
	float m_fRadius;
	float m_fWeight;
};

//---------------------------------------------------------------------------
// GAME ENTITY
//---------------------------------------------------------------------------
struct sGameEntityMeshInit
{
	Ogre::String	m_strName; 
	Ogre::String	m_strMeshName;
	float			m_fScale;
	Ogre::Vector3	m_v3MeshDecal;
};

struct sGameEntityPlaneInit
{
	Ogre::String	m_strName; 
	Ogre::String	m_strMaterialName;
	Ogre::Vector2	m_v2Size;
};

//---------------------------------------------------------------------------
// Ball
//---------------------------------------------------------------------------
struct sBallInit
{
	// Ball setup
	float			m_fMass;
	float			m_fMaxForce;
	float			m_fMaxSpeed;

	// Mesh setup
	sGameEntityMeshInit		m_sMesh;
};

//---------------------------------------------------------------------------
// PLAYER
//---------------------------------------------------------------------------
struct sPlayerBallInit
{
	float					m_fPlayerTargetSpeed;
	float					m_fPlayerForceRatio;
	sBallInit				m_sBall;
};

//---------------------------------------------------------------------------
// SHEEP
//---------------------------------------------------------------------------
struct sSheepBallInit
{
	sFlockingParam			m_sCohesionParam;
	sFlockingParam			m_sSeparationParam;
	sFlockingParam			m_sAlignementParam;
	sFlockingParam			m_sSeparationWolfParam;

	sBallInit				m_sBall;
};


//---------------------------------------------------------------------------
// WOLF
//---------------------------------------------------------------------------
struct sWolfBallInit
{
	sFlockingParam			m_sInterceptionParam;
	sFlockingParam			m_sSeparationParam;
	float                   m_fKillRadius;
	sBallInit				m_sBall;
};

//--------------------------------------------------------------------------
// Folle Deux
//--------------------------------------------------------------------------
struct sFoldInit
{
	float                  m_fFoldRadius;
	sGameEntityMeshInit    m_sMesh;
};

//---------------------------------------------------------------------------
// LEVEL
//---------------------------------------------------------------------------
struct sGameLevel_Init
{
	Ogre::String			m_strName;
	float					m_fLevelDuration;
	uint					m_uiLevelObjective;

	// Camera 
	Ogre::Vector3			m_v3CamPosition;	
	float					m_fCamFov;			

	// Terrain
	sGameEntityPlaneInit	m_sTerrain;

	// Player
	Ogre::Vector3			m_v3PlayerStartingPos;
	sPlayerBallInit			m_sPlayer;

	// Sheeps
	uint					m_uiNbOfSheep;
	Ogre::Vector3*			m_av3SheepStartingPos;
	sSheepBallInit			m_sSheep;

	// Wolves
	uint					m_uiNbOfWolf;
	Ogre::Vector3*			m_av3WolfStartingPos;
	sWolfBallInit			m_sWolf;

	// Fold
	uint					m_uiNbOfFold;
	Ogre::Vector3*			m_av3FoldStartingPos;
	sFoldInit				m_sFold;

};


#endif // #ifndef __BallkeeperInitStructDefine_h_
