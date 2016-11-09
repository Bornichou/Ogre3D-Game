
#include "BKGameEntity.h"
#include "BKGameLevel.h"
#include "BallKeeperApplication.h"

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKGameEntity::BKGameEntity()
{
	// Owner
	m_pLevel = NULL;

	// Starting position
	m_v3StartingPosition = Ogre::Vector3::ZERO;

	// Current position & At
	m_v3Position = Ogre::Vector3::ZERO;
	m_v3AtOrientation = Ogre::Vector3::UNIT_Z;

	// Node & Mesh
	m_pNode = NULL;
	m_pDecalNode = NULL;
	m_pMesh = NULL;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BKGameEntity::~BKGameEntity(void)
{
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::Start()
{
	// Set position to the starting pos
	m_v3Position = m_v3StartingPosition;
	m_pNode->setPosition(m_v3Position);

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::Update(const Ogre::FrameEvent& evt)
{
	//Update
	UpdatePosAndRot(evt);

	//Application de Pos et Rot
	m_pNode->setPosition(m_v3Position);
	m_pNode->setDirection(-m_v3AtOrientation,Ogre::Node::TS_WORLD);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::Stop()
{

}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::UpdatePosAndRot(const Ogre::FrameEvent& evt)
{
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::String  BKGameEntity::GetUniqueGEName(Ogre::String a_strName,uint a_uiIndex)
{
	Ogre::String strUniqueName =  m_pLevel->GetLevelName();
	strUniqueName += "_";
	strUniqueName += a_strName;
	strUniqueName += "_";
	strUniqueName += Ogre::StringConverter::toString(a_uiIndex);

	return strUniqueName;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::InitGameEntityWithMesh(sGameEntityMeshInit a_sGEMeshInit, uint a_uiIndex)
{
	Ogre::String strUniqueName =  GetUniqueGEName(a_sGEMeshInit.m_strName,a_uiIndex);


	// Create the Node
	Ogre::String strNodeName = strUniqueName;
	strNodeName += "_Node";
	m_pNode = m_pLevel->GetLevelNode()->createChildSceneNode(strNodeName);
	// Create the Mesh
	m_pMesh = m_pLevel->GetBKApp()->GetSceneMgr()->createEntity(strUniqueName,a_sGEMeshInit.m_strMeshName);
	m_pMesh->setCastShadows(true);


	// If there is a decal we create a child scene node
		Ogre::String strDecalNodeName = strNodeName;
		strDecalNodeName += "_Decal";
		Ogre::SceneNode* pDecalNode = m_pNode->createChildSceneNode(strDecalNodeName);
		pDecalNode->setPosition(a_sGEMeshInit.m_v3MeshDecal);

		// Attach the mesh to the node
		pDecalNode->attachObject(m_pMesh);
		// Set the scale
		pDecalNode->setScale(a_sGEMeshInit.m_fScale,a_sGEMeshInit.m_fScale,a_sGEMeshInit.m_fScale);

		m_pDecalNode = pDecalNode;
/*
	Ogre::String strCircleName = strUniqueName;
	strCircleName += "_Circle";
	CreateCircle(25.0f,strCircleName);
*/
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::InitGameEntityWithPlane(sGameEntityPlaneInit a_sGEPlaneInit, uint a_uiIndex)
{
	Ogre::String strUniqueName =  GetUniqueGEName(a_sGEPlaneInit.m_strName,a_uiIndex);

	Ogre::String strNodeName = strUniqueName;
	strNodeName += "_Node";

	// Create the Node
	m_pNode = m_pLevel->GetLevelNode()->createChildSceneNode(strNodeName);

	// Create the plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::String strPlaneName = strUniqueName;
	strPlaneName += "_Plane";
	Ogre::MeshManager::getSingleton().createPlane(strPlaneName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, a_sGEPlaneInit.m_v2Size.x, a_sGEPlaneInit.m_v2Size.y, 1, 1, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
	m_pMesh= m_pLevel->GetBKApp()->GetSceneMgr()->createEntity(strUniqueName,strPlaneName);
	m_pMesh->setMaterialName(a_sGEPlaneInit.m_strMaterialName);

	// Attach the mesh to the node
	m_pNode->attachObject(m_pMesh);
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void BKGameEntity::SetStartingPos(Ogre::Vector3 a_v3StartingPos)
{
	m_v3StartingPosition = a_v3StartingPos;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
Ogre::ManualObject* BKGameEntity::CreateCircle(float a_fRadius, Ogre::String a_strUniqueName,Ogre::ColourValue a_rColor)
{
#define BKGAMEENTITY_CREATECIRCLE_NBPOINT 32
#define BKGAMEENTITY_CREATECIRCLE_Y_DECAL 1.0f

	Ogre::ManualObject* pManualCircle = m_pLevel->GetBKApp()->GetSceneMgr()->createManualObject(a_strUniqueName);
	pManualCircle->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

    uint uiPointCount = 0;
	float fAngle = 0.f;
    for(uiPointCount = 0; uiPointCount < BKGAMEENTITY_CREATECIRCLE_NBPOINT; uiPointCount++)
	{
		fAngle = (float) uiPointCount * (2 * Ogre::Math::PI / (float)BKGAMEENTITY_CREATECIRCLE_NBPOINT);
        pManualCircle->position(	a_fRadius * cos(fAngle),
									BKGAMEENTITY_CREATECIRCLE_Y_DECAL,
									a_fRadius * sin(fAngle));
		pManualCircle->colour(a_rColor);
        pManualCircle->index(uiPointCount);
    }
    pManualCircle->index(0);
    pManualCircle->end();

	m_pNode->attachObject(pManualCircle);

	return pManualCircle;
}
