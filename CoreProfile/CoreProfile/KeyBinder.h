#ifndef KEY_BINDER_H
#define KEY_BINDER_H

#include <map>
#include <Windows.h>

/*
#define AEVK_LBUTTON		 VK_LBUTTON	    //!< Left mouse button
#define AEVK_RBUTTON		 VK_RBUTTON	    //!< Right mouse button
#define AEVK_MBUTTON		 VK_MBUTTON	    //!< Middle mouse button

#define AEVK_BACK           VK_BACK         //!< Backspace
#define AEVK_TAB            VK_TAB      
#define AEVK_RETURN		    VK_RETURN		
#define AEVK_LSHIFT		    VK_LSHIFT		
#define AEVK_RSHIFT		    VK_RSHIFT		
#define AEVK_LCTRL		    VK_LCONTROL		
#define AEVK_RCTRL		    VK_RCONTROL		
#define AEVK_LALT		    VK_LMENU		
#define AEVK_RALT		    VK_RMENU		
#define AEVK_PRINTSCREEN    VK_SNAPSHOT
#define AEVK_SCROLLLOCK	    VK_SCROLL
#define AEVK_PAUSE		    VK_PAUSE		
#define AEVK_CAPSLOCK	    VK_CAPITAL

#define AEVK_ESCAPE         VK_ESCAPE   

#define AEVK_SPACE		    VK_SPACE		
#define AEVK_PAGEUP		    VK_PRIOR		
#define AEVK_PAGEDOWN	    VK_NEXT
#define AEVK_END		    VK_END		
#define AEVK_HOME		    VK_HOME		
#define AEVK_LEFT		    VK_LEFT		
#define AEVK_UP			    VK_UP			
#define AEVK_RIGHT		    VK_RIGHT		
#define AEVK_DOWN		    VK_DOWN		
#define AEVK_INSERT		    VK_INSERT		
#define AEVK_DELETE		    VK_DELETE		

#define AEVK_NUMPAD0	    VK_NUMPAD0
#define AEVK_NUMPAD1	    VK_NUMPAD1
#define AEVK_NUMPAD2	    VK_NUMPAD2
#define AEVK_NUMPAD3	    VK_NUMPAD3
#define AEVK_NUMPAD4	    VK_NUMPAD4
#define AEVK_NUMPAD5	    VK_NUMPAD5
#define AEVK_NUMPAD6	    VK_NUMPAD6
#define AEVK_NUMPAD7	    VK_NUMPAD7
#define AEVK_NUMPAD8	    VK_NUMPAD8
#define AEVK_NUMPAD9	    VK_NUMPAD9

#define AEVK_NUM_MULTIPLY   VK_MULTIPLY
#define AEVK_NUM_PLUS	    VK_ADD
#define AEVK_NUM_MINUS	    VK_SUBTRACT
#define AEVK_NUM_PERIOD	    VK_DECIMAL
#define AEVK_NUM_DIVIDE	    VK_DIVIDE
#define AEVK_NUMLOCK	    VK_NUMLOCK

#define AEVK_F1			    VK_F1
#define AEVK_F2			    VK_F2
#define AEVK_F3			    VK_F3
#define AEVK_F4			    VK_F4
#define AEVK_F5			    VK_F5
#define AEVK_F6			    VK_F6
#define AEVK_F7			    VK_F7
#define AEVK_F8			    VK_F8
#define AEVK_F9			    VK_F9
#define AEVK_F10		    VK_F10
#define AEVK_F11		    VK_F11
#define AEVK_F12		    VK_F12

#define AEVK_SEMICOLON	    VK_OEM_1        //!< ; :
#define AEVK_SLASH		    VK_OEM_2		//!< / ?
#define AEVK_BACKQUOTE		VK_OEM_3        //!< ` ~
#define AEVK_LBRACKET	    VK_OEM_4        //!< [ {
#define AEVK_BACKSLASH	    VK_OEM_5        //!< \ |
#define AEVK_RBRACKET	    VK_OEM_6        //!< ] }
#define AEVK_QUOTE		    VK_OEM_7	    //!< ' "

#define AEVK_EQUAL		    VK_OEM_PLUS     //!< = +
#define AEVK_MINUS		    VK_OEM_MINUS    //!< - _
#define AEVK_PERIOD		    VK_OEM_PERIOD   //!< . >
#define AEVK_COMMA		    VK_OEM_COMMA    //!< , <
*/

#define VK_0              0x30        
#define VK_1              0x31        
#define VK_2              0x32        
#define VK_3              0x33        
#define VK_4              0x34        
#define VK_5              0x35        
#define VK_6              0x36        
#define VK_7              0x37        
#define VK_8              0x38        
#define VK_9              0x39        

#define VK_A              0x41        
#define VK_B              0x42        
#define VK_C              0x43        
#define VK_D              0x44        
#define VK_E              0x45        
#define VK_F              0x46        
#define VK_G              0x47        
#define VK_H              0x48        
#define VK_I              0x49        
#define VK_J              0x4A        
#define VK_K              0x4B        
#define VK_L              0x4C        
#define VK_M              0x4D        
#define VK_N              0x4E        
#define VK_O              0x4F        
#define VK_P              0x50        
#define VK_Q              0x51        
#define VK_R              0x52        
#define VK_S              0x53        
#define VK_T              0x54        
#define VK_U              0x55        
#define VK_V              0x56        
#define VK_W              0x57        
#define VK_X              0x58        
#define VK_Y              0x59        
#define VK_Z              0x5A   

class InputManager
{
    std::map<unsigned short, bool> pressed;

public:

    /******************************************************************************/
    /*!
    \fn     bool KeyPressed(unsigned short key)
    \brief
    Returns true if key is pressed, otherwise false
    */
    /******************************************************************************/
    bool KeyPressed(unsigned short key);

    /******************************************************************************/
    /*!
    \fn     bool KeyRelease(unsigned short key)
    \brief
    Returns true if key is pressed, otherwise false
    */
    /******************************************************************************/
    bool KeyRelease(unsigned short key);

    /******************************************************************************/
    /*!
    \fn     bool KeyToggled(unsigned short key)
    \brief
    Returns true if key is pressed, otherwise false
    */
    /******************************************************************************/
    bool KeyToggled(unsigned short key);

    void Update();
};


#endif