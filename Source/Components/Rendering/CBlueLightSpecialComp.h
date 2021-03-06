///////////////////////////////////////////////////////////////////////////////
//	File			:	CBlueLightSpecialComp.h
//	Date			:	7/26/11
//	Mod. Date		:	7/26/11
//	Mod. Initials	:	JL
//	Author			:	Joseph Leybovich
//	Purpose			:	Encapsulates the Blue Light Special for Held Items
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Header Protection
///////////////////////////////////////////////////////////////////////////////
#ifndef _CBLUELIGHTSPECIALCOMP_H_
#define _CBLUELIGHTSPECIALCOMP_H_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include "..\\..\\IComponent.h"
#include "..\\..\\CObject.h"
#include "CRenderComponent.h"
#include "..\\..\\Managers\\Component Managers\\CComponentManager.h"

///////////////////////////////////////////////////////////////////////////////
// Foward Declares
///////////////////////////////////////////////////////////////////////////////
class DXMesh;
class CRenderComponent;

///////////////////////////////////////////////////////////////////////////////
// Blue Light Special Component Class
///////////////////////////////////////////////////////////////////////////////
class CBlueLightSpecialComp : public IComponent
{
private:

	///////////////////////////////////////////////////////////////////////////
	// Data Members
	///////////////////////////////////////////////////////////////////////////

		CObject* m_pParentObj;				// Parent Object
		CObject* m_pBLSObj;					// Blue Light Obj
		CRenderComponent* m_pRenComp;		// BLS Render Comp
		CRenderComponent* m_pEndcapRenComp; // Endcap Render Comp
		bool m_bActive;						// Active Flag

	///////////////////////////////////////////////////////////////////////////
	// Event Handlers
	///////////////////////////////////////////////////////////////////////////
		
		///////////////////////////////////////////////////////////////////////
		// Function: “Update”
		//
		// Return: void
		//
		// Parameters: float fDT - The time since the last Frame
		//
		// Purpose: This Functions is used to Handle Updating BLS Effect by
		//			Translating and Rotating the BLS Obj
		///////////////////////////////////////////////////////////////////////
		void Update(float fDT);

public:

	///////////////////////////////////////////////////////////////////////////
	// Function: “Init”
	//
	// Return: void
	//
	// Parameters: void
	//
	// Purpose: This Functions is used to Initalize the Component by
	//			Registering for Events, Getting and Transforming a BLS Object
	//			with a Render Comp and Binding it to the Parent	Endcap Object.
	///////////////////////////////////////////////////////////////////////////
	void Init(void);

	///////////////////////////////////////////////////////////////////////////
	// Constructor
	///////////////////////////////////////////////////////////////////////////
	CBlueLightSpecialComp(CRenderComponent* pRC) : m_pParentObj(NULL),
												   m_pBLSObj(NULL), 
											       m_pRenComp(NULL), m_pEndcapRenComp(pRC),
											       m_bActive(false)
										      
	{
		// Set Parent
		m_pParentObj = m_pEndcapRenComp->GetParent();

		// Add to Auto Manager
		GetManager()->Add(this);

		// Add Component to Parent
		m_pParentObj->AddComponent(this);

		// Initalize
		Init();
	}

	///////////////////////////////////////////////////////////////////////////
	// Destructor
	///////////////////////////////////////////////////////////////////////////
	~CBlueLightSpecialComp(void)
	{
		GetManager()->Remove(this);
	}

	///////////////////////////////////////////////////////////////////////////
	// Factory Funcs
	///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		// Function: “CreateBlueLightSpecialComponent”
		//
		// Return: CBlueLightSpecialComp* - A New Blue Light Special Component 
		//									connected to the Passed in Object
		//
		// Parameters: CRenderComponent* pcRC - The Parent Remder Component of
		//										the associated Endcap Object
		//
		// Purpose: This Functions is used to Create an Blue Light Special 
		//			Component and Attach it to an Object through C++.
		///////////////////////////////////////////////////////////////////////
		static CBlueLightSpecialComp* CreateBlueLightSpecialComponent(
			CRenderComponent* pcRC)
		{
			return MMNEW(CBlueLightSpecialComp(pcRC));
		}

	///////////////////////////////////////////////////////////////////////////////
	// Event Callbacks
	///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////
		// Function: “UpdateCallback”
		//
		// Return: void
		//
		// Parameters: IEvent* pEvent	 - Event Data
		//			   IComponent* pComp - The Listening Component
		//
		// Purpose: This Functions is used to Handle Updating the Passed in
		//			Component's BLS Effect by Translating and Rotating the BLS Obj
		///////////////////////////////////////////////////////////////////////////
		static void UpdateCallback(IEvent* pEvent, IComponent* pComp);

		///////////////////////////////////////////////////////////////////////////
		// Function: “ActivateCallback”
		//
		// Return: void
		//
		// Parameters: IEvent* pEvent	 - Event Data
		//			   IComponent* pComp - The Listening Component
		//
		// Purpose: This Functions is used to Handle Activating of the Passed in
		//			Component's BLS Effect.
		///////////////////////////////////////////////////////////////////////////
		static void ActivateCallback(IEvent* pEvent, IComponent* pComp);

		///////////////////////////////////////////////////////////////////////////
		// Function: “DeactivateCallback”
		//
		// Return: void
		//
		// Parameters: IEvent* pEvent	 - Event Data
		//			   IComponent* pComp - The Listening Component
		//
		// Purpose: This Functions is used to Handle Deactivating of the Passed in
		//			Component's BLS Effect.
		///////////////////////////////////////////////////////////////////////////
		static void DeactivateCallback(IEvent* pEvent, IComponent* pComp);

	///////////////////////////////////////////////////////////////////////////
	// Accessors
	///////////////////////////////////////////////////////////////////////////
	
		// Parent Object
		CObject* GetParent(void) { return m_pParentObj; }
	
		// Active Flag
		bool IsActive(void)		 { return m_bActive;    }

		// Auto-Manager
		static CComponentManager<CBlueLightSpecialComp>* GetManager(void)
		{
			// Auto-Manager
			static CComponentManager<CBlueLightSpecialComp> m_cManager;

			return &m_cManager;
		}

	///////////////////////////////////////////////////////////////////////////
	// Mutators
	///////////////////////////////////////////////////////////////////////////
	
		// Active Flag
		void SetActive(bool bActive) { m_bActive = bActive; }
};
#endif // _CBLUELIGHTSPECIALCOMP_H_