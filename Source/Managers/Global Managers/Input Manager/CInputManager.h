////////////////////////////////////////////////////////////////////////////////
// File:	�CInputManager.h�
//
// Author: Mac Reichelt (MR)
// 
// Description: This class is used to manage all input from both the keyboard 
//		and a gamepad, It sends events based upon the input it receives from 
//		either device that correspond to the apporpriate action bound to those
//		keys/buttons.
//
// Stipulations: There should only be one instance of the Input Manager at any
//		given time.
//
// Interface: The CGame object is responsible for handling the creation and 
//		destruction of the Input Manager.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _CINPUTMANAGER_H_
#define _CINPUTMANAGER_H_

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <xinput.h>
#pragma comment(lib, "xinput.lib")

#include <queue>
#include <string>
using namespace std;

#include "../State Manager/CStateManager.h"

enum {CMD_ACCEPT = 1, CMD_BACK, CMD_ACCELERATE, CMD_DECELERATE, CMD_SHOVELEFT,
CMD_SHOVERIGHT, CMD_STEERLEFT, CMD_STEERRIGHT, CMD_UP, CMD_DOWN, CMD_LEFT, 
CMD_RIGHT, CMD_MENU};

////////////////////////////////////////////////////////////////////////////////
//	Frame Structure
//
// Description: Holds data for a single frame of animation.
//
// Stipulations: CAnimationManager and tAnimation have access to this
//		structure.
//
// Interface: CAnimationManager is the only class that can access this
//		structure. This struct also interacts with tAnimation and 
//		tAnimTimeStamp.
////////////////////////////////////////////////////////////////////////////////
struct TCommand
{
	int		m_nID;
	int		m_nControllerButton;
	BYTE	m_chKeyboardKey;
};
////////////////////////////////////////////////////////////////////////////////

// Forward Declarations
class IComponent;
class IEvent;

class CInputManager
{
private:
	// DirectInput Devices
	IDirectInput8*			m_pDin;			// The DirectInput COM object
	IDirectInputDevice8*	m_pKeyboard;	// The keyboard device

	// Current and Previous Keyboard States
	BYTE	m_chKeys[256];	// The state of the keyboard this frame
	BYTE	m_chPrevKeys[256];// The state of the keyboard last frame

	// Current and Previous Controller States
	XINPUT_STATE*	m_pController;	// Struct w/ the state of the connected gamepad
	DWORD			m_dwPrevState;	//Struct w/ the state of the connected gamepad last frame

	// If Controller
	bool	m_bControllerConnected; // If there is a controller connected

	// Menu Input
	TCommand	m_tAccept;		// The key and button used for accepting menu options
	TCommand	m_tBack;		// The key and button used for return to the previous menu
	TCommand	m_tUp;			// The key and button used for the Up command
	TCommand	m_tDown;		// The key and button used for the Down command
	TCommand	m_tLeft;		// The key and button used for the Left command
	TCommand	m_tRight;		// The key and button used for the Right command

	// Gameplay Input
	TCommand	m_tMenu;		// The key and button used for accessing the Pause menu during gameplay
	TCommand	m_tAccelerate;	// The key and button used for accelerating the player's cart
	TCommand	m_tDecelerate;	// The key and button used for decelerating the player's cart
	TCommand	m_tSteerLeft;	// The key and button used to steer the player's cart left
	TCommand	m_tSteerRight;	// The key and button used to steer the player's cart right
	TCommand	m_tShoveLeft;	// The key and button used to shove left
	TCommand	m_tShoveRight;	// The key and button used to shove right
	// TODO: Add more controls

	queue<TCommand>	m_cInput;		// Queue of actions registered from input

	string*	m_szKeyStrings;// An array of strings that describe the DIK key codes

	EGameState	m_eGameState;	// The current game state, input done accordingly

	void (CInputManager::*m_pfGetInput)();

	//	Constructor
	CInputManager();

	//	Trilogy of Evil
	~CInputManager();
	CInputManager(const CInputManager&);
	CInputManager& operator=(const CInputManager&);

public:
////////////////////////////////////////////////////////////////////////////////
// Function:	�GetInstance�
//
// Return:		CInputManager*	-	The instance of the class
//
// Parameters:	void
//
// Purpose:		This function is used to get an instance of a singleton class
////////////////////////////////////////////////////////////////////////////////
	static CInputManager* GetInstance();

	static void GetInput(IEvent*, IComponent*);
	static void InputStateChange(IEvent*, IComponent*);
	static void Shutdown(IEvent*, IComponent*);
	
	void GetInputIntro();
	void GetInputMenu();
	void GetInputGameplay();

	EGameState GetState()
	{
		return m_eGameState;
	}
////////////////////////////////////////////////////////////////////////////////
// Function:	�Initialize�
//
// Return:		void
//
// Parameters:	HWND hWnd			-	the handle to the window
//				HINSTANCE hInstance	-	the handle to the instance
//
// Purpose:		This function is used to initialize the Input Manager. All 
//				DirectX objects are initialized	and devices are polled.
////////////////////////////////////////////////////////////////////////////////
	void Initialize(HWND hWnd, HINSTANCE hInstance);

////////////////////////////////////////////////////////////////////////////////
// Function:	�Shutdown�
//
// Return:		void
//
// Parameters:	void
//
// Purpose:		This function is used to shutdown the Input Manager. All DirectX
//				objects are released.
////////////////////////////////////////////////////////////////////////////////
	void Shutdown();

////////////////////////////////////////////////////////////////////////////////
// Function:	�ReadDevices�
//
// Return:		void
//
// Parameters:	void
//
// Purpose:		This function is used to read the current devices and collect 
//				info on their current state.
////////////////////////////////////////////////////////////////////////////////
	void ReadDevices();

////////////////////////////////////////////////////////////////////////////////
// Function:	�ClearInput�
//
// Return:		void
//
// Parameters:	void
//
// Purpose:		This function is used to clear the input for all devices and the
//				Input queue.
////////////////////////////////////////////////////////////////////////////////
	void ClearInput();

////////////////////////////////////////////////////////////////////////////////
// Function:	�GetAction�
//
// Return:		int	-	the enumerated value of the action at the front of the 
//						input queue
//
// Parameters:	void
//
// Purpose:		This function is used to return the enumerated value of the 
//				action at the front of the input queue and pop it from the queue
////////////////////////////////////////////////////////////////////////////////
	//int GetAction();

////////////////////////////////////////////////////////////////////////////////
// Function:	�PeekAction�
//
// Return:		int	-	the enumerated value of the action at the front of the 
//						input queue
//
// Parameters:	void
//
// Purpose:		This function is used to return the enumerated value of the 
//				action at the front	of the input queue.
////////////////////////////////////////////////////////////////////////////////
	//int PeekAction();

	BYTE SetKeyboardCommand(int nCommandID, BYTE uchKey = 0);
	int SetControllerCommand(int nCommandID, int nButton = 0);
	string GetStringController(int nButton);
	string GetStringKeyboard(unsigned char uchKey);
	void InitKeyStrings();

	string SetCommand(bool bController, int nCommandID);
	bool IsControllerConnected();

	int GetControllerButton(int nCommand);
	BYTE GetKeyboardKey(int nCommand);
};

#endif