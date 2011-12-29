/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#ifndef __WIN_LOCAL_H__
#define __WIN_LOCAL_H__

#if defined(_MFC_VER) && !defined(_D3SDK) && !defined(GAME_DLL)
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// prevent auto literal to string conversion
#include "tools/comafx/StdAfx.h"
#endif

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <mmsystem.h>
#include <mmreg.h>

#define DIRECTINPUT_VERSION  0x0800			// was 0x0700 with the old mssdk
#include <dinput.h>

#include <GL/gl.h>

#include "framework/CVarSystem.h"
#include "renderer/wglext.h"		// windows OpenGL extensions
#include "sys/sys_public.h"

// WGL_ARB_extensions_string
extern	PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;

// WGL_EXT_swap_interval
extern	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

// WGL_ARB_pixel_format
extern	PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB;
extern	PFNWGLGETPIXELFORMATATTRIBFVARBPROC wglGetPixelFormatAttribfvARB;
extern	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

// WGL_ARB_pbuffer
extern	PFNWGLCREATEPBUFFERARBPROC	wglCreatePbufferARB;
extern	PFNWGLGETPBUFFERDCARBPROC	wglGetPbufferDCARB;
extern	PFNWGLRELEASEPBUFFERDCARBPROC	wglReleasePbufferDCARB;
extern	PFNWGLDESTROYPBUFFERARBPROC	wglDestroyPbufferARB;
extern	PFNWGLQUERYPBUFFERARBPROC	wglQueryPbufferARB;

// WGL_ARB_render_texture
extern	PFNWGLBINDTEXIMAGEARBPROC		wglBindTexImageARB;
extern	PFNWGLRELEASETEXIMAGEARBPROC	wglReleaseTexImageARB;
extern	PFNWGLSETPBUFFERATTRIBARBPROC	wglSetPbufferAttribARB;


#define	MAX_OSPATH			256

#define	WINDOW_STYLE	(WS_OVERLAPPED|WS_BORDER|WS_CAPTION|WS_VISIBLE | WS_THICKFRAME)

void	Sys_QueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr );

void	Sys_CreateConsole( void );
void	Sys_DestroyConsole( void );

char	*Sys_ConsoleInput (void);
char	*Sys_GetCurrentUser( void );

void	Win_SetErrorText( const char *text );

int		MapKey (int key);


// Input subsystem

void	IN_Init (void);
void	IN_Shutdown (void);
// add additional non keyboard / non mouse movement on top of the keyboard move cmd

void	IN_DeactivateMouseIfWindowed( void );
void	IN_DeactivateMouse( void );
void	IN_ActivateMouse( void );

void	IN_Frame( void );

int		IN_DIMapKey( int key );

void	DisableTaskKeys( BOOL bDisable, BOOL bBeep, BOOL bTaskMgr );


// window procedure
LONG WINAPI MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void Conbuf_AppendText( const char *msg );

struct Win32Vars_t {
	HWND			hWnd;
	HINSTANCE		hInstance;

	bool			activeApp;			// changed with WM_ACTIVATE messages
	bool			mouseReleased;		// when the game has the console down or is doing a long operation
	bool			movingWindow;		// inhibit mouse grab when dragging the window
	bool			mouseGrabbed;		// current state of grab and hide

	OSVERSIONINFOEX	osversion;

	// when we get a windows message, we store the time off so keyboard processing
	// can know the exact time of an event (not really needed now that we use async direct input)
	int				sysMsgTime;

	bool			windowClassRegistered;

	WNDPROC			wndproc;

	HDC				hDC;							// handle to device context
	HGLRC			hGLRC;						// handle to GL rendering context
	PIXELFORMATDESCRIPTOR pfd;
	int				pixelformat;

	HINSTANCE		hinstOpenGL;	// HINSTANCE for the OpenGL library

	int				desktopBitsPixel;
	int				desktopWidth, desktopHeight;

	bool			cdsFullscreen;

	FILE			*log_fp;

	unsigned short	oldHardwareGamma[3][256];
	// desktop gamma is saved here for restoration at exit

	static idCVar	sys_arch;
	static idCVar	in_mouse;
	static idCVar	win_allowAltTab;
	static idCVar	win_notaskkeys;
	static idCVar	win_username;
	static idCVar	win_xpos;			// archived X coordinate of window position
	static idCVar	win_ypos;			// archived Y coordinate of window position
	static idCVar	win_outputDebugString;
	static idCVar	win_outputEditString;
	static idCVar	win_viewlog;
	static idCVar	win_timerUpdate;
	static idCVar	win_allowMultipleInstances;

	HINSTANCE		hInstDI;			// direct input

	LPDIRECTINPUT8			g_pdi;
	LPDIRECTINPUTDEVICE8	g_pMouse;
	LPDIRECTINPUTDEVICE8	g_pKeyboard;

	int				wglErrors;
	// SMP acceleration vars

};

extern Win32Vars_t	win32;

#endif /* !__WIN_LOCAL_H__ */
