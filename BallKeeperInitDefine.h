/*
-----------------------------------------------------------------------------
Filename:    BallKeeperInitDefine.h
-----------------------------------------------------------------------------
*/
#ifndef __BallKeeperInitDefine_h_
#define __BallKeeperInitDefine_h_

#include "BallKeeperApplication.h"
#include "BallKeeperInitStructDefine.h"



// Standard terrain (grass)
static sGameEntityPlaneInit	g_sStandardTerrain =
{
	"StdGround",					// m_strName
	"Examples/GrassFloor",			// m_strMaterialName
	Ogre::Vector2(500.0f, 500.0f)	// m_v2Size
};

// Standard player
static sPlayerBallInit	g_sStandardPlayer =
{
	150.0f,			// m_fPlayerTargetSpeed;
	10.0f,			// m_fPlayerForceRatio
	{
		1.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		1000.0f,		// m_fMaxSpeed;
		{
			"PlayerStd",							// m_strName;
			"ogrehead.mesh",						// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 8.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};

// Standard sheep
static sSheepBallInit	g_sStandardSheep =
{
	{ 100.0f, 8.0f },		// m_sCohesionParam;
	{ 19.0f, 100.0f },		// m_sSeparationParam;
	{ 100.0f, 2.0f },		// m_sAlignementParam;
	{ 50.0f, 200.0f },		// m_sSeparationWolfParam;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		120.0f,		// m_fMaxSpeed;
		{
			"SheepStd",								// m_strName;
			"penguin.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 8.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};

// Standard Wolf
static sWolfBallInit	g_sStandardWolf =
{
	{ 100.0f, 5.0f },		// m_sInterceptionParam;
	{ 10.0f, 100.0f },		// m_sSeparationParam;
	5.0f,                  //m_fKillRadius;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		120.0f,		// m_fMaxSpeed;
		{
			"WolfStd",								// m_strName;
			"robot.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 0.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};



static sFoldInit g_sStandardFold =
{
	50.0f,                               //fFoldRadius;

	{
		"Foldstd",	                      // m_strName;
		"tudorhouse.mesh",	                  // m_strMeshName;
		0.05f,                             // m_fScale;
		Ogre::Vector3(0.0f,550.0f*0.05f,0.0f)	  // m_v3MeshDecal;
	}
};

/*****************************************************************/
/*                       TUTORIAL LEVEL 0                               */
/*****************************************************************/

static sSheepBallInit	g_sSheepTutorial0 =
{
	{ 70.0f, 8.0f },		// m_sCohesionParam;
	{ 19.0f, 100.0f },		// m_sSeparationParam;
	{ 100.0f, 2.0f },		// m_sAlignementParam;
	{ 50.0f, 200.0f },		// m_sSeparationWolfParam;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		120.0f,		// m_fMaxSpeed;
		{
			"SheepStd",								// m_strName;
			"penguin.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 8.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};


// Standard terrain (grass)
static sGameEntityPlaneInit	g_sTerrainTutorial0 =
{
	"GroundTutorial0",					// m_strName
	"Examples/GrassFloor",			// m_strMaterialName
	Ogre::Vector2(100.0f, 500.0f)	// m_v2Size
};

static sFoldInit g_sFoldTutorial0 =
{
	50.0f,                               //fFoldRadius;

	{
		"Foldstd",	                      // m_strName;
		"tudorhouse.mesh",	                  // m_strMeshName;
		0.1f,                             // m_fScale;
		Ogre::Vector3(0.0f,550.0f*0.1f,0.0f)	  // m_v3MeshDecal;
	}
};

static Ogre::Vector3 g_av3Tutorial0SheepStartingPos[200] =
{
	Ogre::Vector3(0.0f ,0.0f ,-180.0f)  //un sheep placé devant le joueur les 9 autres au centre du terrain
};

static Ogre::Vector3 g_av3Tutorial0WolfStartingPos[5];


static Ogre::Vector3 g_av3Tutorial0FoldStartingPos[2] =
{
	Ogre::Vector3(0.0f ,0.0f ,200.0f)
};

static sGameLevel_Init g_sTutorial0 =
{
	"Tutorial ",			// m_strName
	50.0f,					// m_fLevelDuration
	5,						// m_uiLevelObjective

	// Camera
	Ogre::Vector3(0.0f ,400.0f ,-400.0f),	//	m_v3CamPosition;
	40.0f,									//	m_fCamFov;

	// Terrain
	g_sTerrainTutorial0,

	// Player
	Ogre::Vector3(0.0f, 0.0f, -220.0f),	// m_v3PlayerStartingPos;
	g_sStandardPlayer,

	// Sheeps
	10,									// m_uiNbOfSheep;
	g_av3Tutorial0SheepStartingPos,		// m_av3SheepStartingPos;
	g_sSheepTutorial0,					// m_sSheep;

	// Wolves
	0,					//m_uiNbOfWolf;
	g_av3Tutorial0WolfStartingPos,			//m_av3WolfStartingPos;
	g_sStandardWolf,			//m_sWolf;

	// Fold
	1,					//m_uiNbOfFold;
	g_av3Tutorial0FoldStartingPos,		//m_av3FoldStartingPos;
	g_sFoldTutorial0			//m_sFold;

};

/*****************************************************************/
/*                        LEVEL 1                                */
/*****************************************************************/


static sWolfBallInit	g_sWolfLevel1 =
{
	{ 150.0f, 5.0f },		// m_sInterceptionParam;
	{ 10.0f, 100.0f },		// m_sSeparationParam;
	5.0f,                  //m_fKillRadius;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		240.0f,		// m_fMaxSpeed;
		{
			"WolfStd",								// m_strName;
			"robot.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 0.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};


// Standard terrain (grass)
static sGameEntityPlaneInit	g_sTerrainLevel1 =
{
	"GroundLevel1",					// m_strName
	"Examples/GrassFloor",			// m_strMaterialName
	Ogre::Vector2(1000.0f, 1000.0f)	// m_v2Size
};


static sFoldInit g_sFoldLevel1 =
{
	100.0f,                               //fFoldRadius;

	{
		"Foldstd",	                      // m_strName;
		"tudorhouse.mesh",	                  // m_strMeshName;
		0.1f,                             // m_fScale;
		Ogre::Vector3(0.0f,550.0f*0.1f,0.0f)	  // m_v3MeshDecal;
	}
};

static Ogre::Vector3 g_av3Level1SheepStartingPos[200] =
{
	Ogre::Vector3(0.0f ,0.0f ,0.0f),
};

static Ogre::Vector3 g_av3Level1WolfStartingPos[5]
{
    Ogre::Vector3(0.0f ,0.0f ,400.0f),
    Ogre::Vector3(100.0f ,0.0f ,300.0f),
    Ogre::Vector3(200.0f ,0.0f ,200.0f),
    Ogre::Vector3(300.0f ,0.0f ,100.0f),
     Ogre::Vector3(400.0f ,0.0f ,0.0f),
};


static Ogre::Vector3 g_av3Level1FoldStartingPos[2] =
{
	Ogre::Vector3(400.0f ,0.0f ,400.0f)
};

static sGameLevel_Init g_sLevel1 =
{
	"Level ",			// m_strName
	50.0f,					// m_fLevelDuration
	5,						// m_uiLevelObjective

	// Camera
	Ogre::Vector3(0.0f ,400.0f ,-400.0f),	//	m_v3CamPosition;
	40.0f,									//	m_fCamFov;

	// Terrain
	g_sTerrainLevel1,

	// Player
	Ogre::Vector3(0.0f, 0.0f, -40.0f),	// m_v3PlayerStartingPos;
	g_sStandardPlayer,

	// Sheeps
	200,									// m_uiNbOfSheep;
	g_av3Level1SheepStartingPos,		// m_av3SheepStartingPos;
	g_sSheepTutorial0,					// m_sSheep;

	// Wolves
	5,					//m_uiNbOfWolf;
	g_av3Level1WolfStartingPos,			//m_av3WolfStartingPos;
	g_sWolfLevel1,			//m_sWolf;

	// Fold
	1,					//m_uiNbOfFold;
	g_av3Level1FoldStartingPos,		//m_av3FoldStartingPos;
	g_sFoldLevel1			//m_sFold;

};

/*****************************************************************/
/*                        LEVEL 2                                */
/*****************************************************************/

static sWolfBallInit	g_sWolfLevel2 =
{
	{ 70.0f, 5.0f },		// m_sInterceptionParam;
	{ 10.0f, 100.0f },		// m_sSeparationParam;
	5.0f,                  //m_fKillRadius;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		120.0f,		// m_fMaxSpeed;
		{
			"WolfStd",								// m_strName;
			"robot.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 0.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};

static Ogre::Vector3 g_av3Level2SheepStartingPos[6] =
{
	Ogre::Vector3(-200.0f ,0.0f, 200.0f),
	Ogre::Vector3(-200.0f, 0.0f, 200.0f),
	Ogre::Vector3(-200.0f, 0.0f, 200.0f),
	Ogre::Vector3(200.0f ,0.0f, -200.0f),
	Ogre::Vector3(200.0f, 0.0f, -200.0f),
	Ogre::Vector3(200.0f, 0.0f, -200.0f),

};

static Ogre::Vector3 g_av3Level2WolfStartingPos[6] =
{
	Ogre::Vector3(50.0f ,0.0f ,50.0f),
	Ogre::Vector3(-50.0f, 0.0f, -50.0f),
	Ogre::Vector3(50.0f ,0.0f ,200.0f),
	Ogre::Vector3(-50.0f, 0.0f, -200.0f),
	Ogre::Vector3(-250.0f, 0.0f, 0.0f),
	Ogre::Vector3(250.0f, 0.0f, 0.0f)

};

static Ogre::Vector3 g_av3Level2FoldStartingPos[2] =
{
	Ogre::Vector3(150.0f ,0.0f ,150.0f),
	Ogre::Vector3(-150.0f ,0.0f ,-150.0f)
};

static sGameLevel_Init g_sLevel2 =
{
	"Level ",			// m_strName
	80.0f,					// m_fLevelDuration
	4,						// m_uiLevelObjective

	// Camera
	Ogre::Vector3(0.0f ,400.0f ,-400.0f),	//	m_v3CamPosition;
	40.0f,									//	m_fCamFov;

	// Terrain
	g_sStandardTerrain,

	// Player
	Ogre::Vector3(0.0f, 0.0f, -220.0f),	// m_v3PlayerStartingPos;
	g_sStandardPlayer,

	// Sheeps
	6,									// m_uiNbOfSheep;
	g_av3Level2SheepStartingPos,		// m_av3SheepStartingPos;
	g_sStandardSheep,					// m_sSheep;

	// Wolves
	6,					//m_uiNbOfWolf;
	g_av3Level2WolfStartingPos,			//m_av3WolfStartingPos;
	g_sWolfLevel2,			//m_sWolf;

	// Fold
	2,					//m_uiNbOfFold;
	g_av3Level2FoldStartingPos,		//m_av3FoldStartingPos;
	g_sStandardFold			//m_sFold;

};

/*****************************************************************/
/*                        LEVEL 3                                */
/*****************************************************************/

static sWolfBallInit	g_sWolfLevel3 =
{
	{ 100.0f, 5.0f },		// m_sInterceptionParam;
	{ 10.0f, 100.0f },		// m_sSeparationParam;
	5.0f,                  //m_fKillRadius;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		180.0f,		// m_fMaxSpeed;
		{
			"WolfStd",								// m_strName;
			"robot.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 0.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};


static Ogre::Vector3 g_av3Level3SheepStartingPos[4] =
{
	Ogre::Vector3(250.0f ,0.0f ,250.0f),
	Ogre::Vector3(-250.0f, 0.0f, -250.0f),
	Ogre::Vector3(-250.0f, 0.0f, 250.0f),
	Ogre::Vector3(250.0f, 0.0f, -250.0f)
};

static Ogre::Vector3 g_av3Level3WolfStartingPos[4] =
{
	Ogre::Vector3(100.0f ,0.0f , 0.0f),
	Ogre::Vector3(-100.0f, 0.0f, 0.0f),
	Ogre::Vector3(0.0f ,0.0f , 100.0f),
	Ogre::Vector3(0.0f, 0.0f, -100.0f)

};

static Ogre::Vector3 g_av3Level3FoldStartingPos[1] =
{
	Ogre::Vector3(0.0f ,0.0f ,0.0f)
};

static sGameLevel_Init g_sLevel3 =
{
	"Level ",			// m_strName
	30.0f,					// m_fLevelDuration
	2,						// m_uiLevelObjective

	// Camera
	Ogre::Vector3(0.0f ,400.0f ,-400.0f),	//	m_v3CamPosition;
	40.0f,									//	m_fCamFov;

	// Terrain
	g_sStandardTerrain,

	// Player
	Ogre::Vector3(0.0f, 0.0f, -250.0f),	// m_v3PlayerStartingPos;
	g_sStandardPlayer,

	// Sheeps
	4,									// m_uiNbOfSheep;
	g_av3Level3SheepStartingPos,		// m_av3SheepStartingPos;
	g_sStandardSheep,					// m_sSheep;

	// Wolves
	4,					//m_uiNbOfWolf;
	g_av3Level3WolfStartingPos,			//m_av3WolfStartingPos;
	g_sWolfLevel3,			//m_sWolf;

	// Fold
	1,					//m_uiNbOfFold;
	g_av3Level3FoldStartingPos,		//m_av3FoldStartingPos;
	g_sStandardFold			//m_sFold;

};


/*****************************************************************/
/*                        LEVEL 4                                */
/*****************************************************************/

static sGameEntityPlaneInit	g_sTerrainLevel4 =
{
	"GroundLevel1",					// m_strName
	"Examples/GrassFloor",			// m_strMaterialName
	Ogre::Vector2(300.0f, 1000.0f)	// m_v2Size
};


static sWolfBallInit	g_sWolfLevel4 =
{
	{ 40.0f, 5.0f },		// m_sInterceptionParam;
	{ 10.0f, 100.0f },		// m_sSeparationParam;
	5.0f,                  //m_fKillRadius;
	{
		3.0f,			// m_fMass;
		10000.0f,		// m_fMaxForce;
		240.0f,		// m_fMaxSpeed;
		{
			"WolfStd",								// m_strName;
			"robot.mesh",							// m_strMeshName;
			0.3f,									// m_fScale;
			Ogre::Vector3(0.0f, 0.0f, 0.0f)			// m_v3MeshDecal
		}
	}
};

static Ogre::Vector3 g_av3Level4SheepStartingPos[1] =
{
	Ogre::Vector3(0.0f ,0.0f ,-450.0f)
};

static Ogre::Vector3 g_av3Level4WolfStartingPos[16] =
{
	Ogre::Vector3(0.0f ,0.0f ,300.0f),
	Ogre::Vector3(-100.0f, 0.0f, 250.0f),
	Ogre::Vector3(100.0f, 0.0f, 250.0f),
	Ogre::Vector3(0.0f ,0.0f ,180.0f),
	Ogre::Vector3(-100.0f, 0.0f, 150.0f),
	Ogre::Vector3(100.0f, 0.0f, 150.0f),
	Ogre::Vector3(0.0f ,0.0f ,70.0f),
	Ogre::Vector3(-100.0f, 0.0f, 0.0f),
	Ogre::Vector3(100.0f, 0.0f, 0.0f),

	Ogre::Vector3(0.0f ,0.0f ,-300.0f),
	Ogre::Vector3(-100.0f, 0.0f, -250.0f),
	Ogre::Vector3(100.0f, 0.0f, -250.0f),
	Ogre::Vector3(0.0f ,0.0f ,-180.0f),
	Ogre::Vector3(-100.0f, 0.0f, -150.0f),
	Ogre::Vector3(100.0f, 0.0f, -150.0f),
	Ogre::Vector3(0.0f ,0.0f ,-70.0f),

};

static Ogre::Vector3 g_av3Level4FoldStartingPos[1] =
{
	Ogre::Vector3(0.0f ,0.0f ,350.0f),
};

static sGameLevel_Init g_sLevel4 =
{
	"Level ",			// m_strName
	20.0f,					// m_fLevelDuration
	1,						// m_uiLevelObjective

	// Camera
	Ogre::Vector3(0.0f ,400.0f ,-400.0f),	//	m_v3CamPosition;
	40.0f,									//	m_fCamFov;

	// Terrain
	g_sTerrainLevel4,

	// Player
	Ogre::Vector3(0.0f, 0.0f, -500.0f),	// m_v3PlayerStartingPos;
	g_sStandardPlayer,

	// Sheeps
	1,									// m_uiNbOfSheep;
	g_av3Level4SheepStartingPos,		// m_av3SheepStartingPos;
	g_sStandardSheep,					// m_sSheep;

	// Wolves
	16,									//m_uiNbOfWolf;
	g_av3Level4WolfStartingPos,			//m_av3WolfStartingPos;
	g_sWolfLevel4,					//m_sWolf;

	// Fold
	1,									//m_uiNbOfFold;
	g_av3Level4FoldStartingPos,			//m_av3FoldStartingPos;
	g_sStandardFold						//m_sFold;

};

static sGameLevel_Init g_asBallKeeperInit[BK_LEVEL_NB] =
{

	g_sTutorial0,
	g_sLevel1,
	g_sLevel2,
	g_sLevel3,
	g_sLevel4

};


#endif // #ifndef __BallKeeperInitDefine_h_
