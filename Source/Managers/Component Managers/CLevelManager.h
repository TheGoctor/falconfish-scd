/*******************************************************************************
 * Filename:  		CLevelManager.h
 * Date:      		04/09/2011
 * Mod. Date: 		04/16/2011
 * Mod. Initials:	JS
 * Author:    		Jesse A. Stanciu
 * Purpose:   		This manager will be used to
 *					spawn items on the level and
 *					cycle through them.
 ******************************************************************************/

#ifndef _CLEVELMANAGER_H_
#define _CLEVELMANAGER_H_

#include <D3dx9math.h>
#include <list>
using std::list;

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "..\Global Managers\Memory Manager\CAllocator.h"

class CEventManager;
class IEvent;
class IComponent;
class CObject;
class CRenderComponent;

class CLevelManager
{
public:
	struct CNode
	{
		char szName[64];
		D3DXMATRIX tLocalMatrix;
		D3DXMATRIX tWorldMatrix;
	};

private:


	list<CRenderComponent*, CAllocator<CRenderComponent*>> m_cLevelRenderComps;
	list<CRenderComponent*, CAllocator<CRenderComponent*>> m_cLevelCollisionRenderComps;
	
	int	m_objectcount;
	bool m_bDrawCollision;
	bool m_bDrawGeometry;

	CNode* m_levelNodes;
	CNode* m_shadowNodes;

	CNode	m_pCheckoutNode;

	// Constructor
	CLevelManager();

	/////////////////////
	// Trilogy of Evil //
	/////////////////////
	~CLevelManager();
	CLevelManager(const CLevelManager&) {}
	CLevelManager& operator=(const CLevelManager&) {}

	void BuildLevel(char* szNodeMap);
	void DrawCollision();
	void DrawGeometry();
	bool GetDrawCollision() { return m_bDrawCollision; }
	bool GetDrawGeometry() { return m_bDrawGeometry; }

	void FindAndCreateShadow(CObject* pParentObj, ERenderContext eObjRenContext);
	void BuildShadows(char* szNodeMap);

public:
	
	static CLevelManager* GetInstance()
	{
		static CLevelManager cLevelManager;
		return &cLevelManager;
	}

	void Init();
	static void Shutdown(IEvent*, IComponent*);
	static void Update(IEvent*, IComponent*);
	static void Level1SelectedCallback(IEvent*, IComponent*);
	static int  ToggleCollisionVision(lua_State* ptr);
	static int	 ToggleGeometryVision(lua_State* ptr);

	void AddRenderCollision(CRenderComponent* pRC);

	inline CNode* GetLevelNodes()
	{
		return m_levelNodes;
	}

	inline int GetNumNodes()
	{
		return m_objectcount;
	}

	inline CNode* GetCheckoutNode()
	{
		return &m_pCheckoutNode;
	}

	void LoadLocations();

	// Mutators
};

#endif