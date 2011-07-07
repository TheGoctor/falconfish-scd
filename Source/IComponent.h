////////////////////////////////////////////////////////////////////////////////
//	File			:	IComponent.h
//	Date			:	3/29/11
//	Mod. Date		:	3/29/11
//	Mod. Initials	:	MR
//	Author			:	Mac Reichelt
//	Purpose			:	Parent class for all component classes so they may be
//						added to the Object Class.
////////////////////////////////////////////////////////////////////////////////

#ifndef _ICOMPONENT_H_
#define _ICOMPONENT_H_

class IComponent
{
	bool m_bIsActive;

public:
	IComponent() : m_bIsActive(true) { }

	bool GetIsActive() { return m_bIsActive; }
	void SetIsActive(bool bActive) { m_bIsActive = bActive; }
	void ToggleIsActive() { m_bIsActive = !m_bIsActive; }
};

#endif