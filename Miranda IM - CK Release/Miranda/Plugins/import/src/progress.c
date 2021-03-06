/*
Import plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright (C) 2000-2012 Martin �berg
									Richard Hughes
									Dmitry Kuzkin
									George Hazan

Copyright 2000-2012 Miranda IM project,
all portions of this codebase are copyrighted to the people
listed in contributors.txt.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

===============================================================================

File name      : $HeadURL: 
Revision       : $Revision: 
Last change on : $Date: 
Last change by : $Author:
$Id$		   : $Id$:

===============================================================================
*/

#include <windows.h>
#include <stdio.h>
#include <commctrl.h>

#include "import.h"
#include "../resource.h"

#define PROGM_START   (WM_USER+100)

INT_PTR CALLBACK FinishedPageProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam);

void (*DoImport)(HWND);

INT_PTR CALLBACK ProgressPageProc(HWND hdlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hdlg);
		SendMessage(GetParent(hdlg),WIZM_DISABLEBUTTON,0,0);
		SendMessage(GetParent(hdlg),WIZM_DISABLEBUTTON,1,0);
		SendMessage(GetParent(hdlg),WIZM_DISABLEBUTTON,2,0);
		SendDlgItemMessage(hdlg,IDC_PROGRESS,PBM_SETRANGE,0,MAKELPARAM(0,100));
		PostMessage(hdlg,PROGM_START,0,0);
		return TRUE;

	case PROGM_SETPROGRESS:
		SendDlgItemMessage(hdlg,IDC_PROGRESS,PBM_SETPOS,wParam,0);
		break;

	case PROGM_ADDMESSAGE:
		{
			int i=SendDlgItemMessage(hdlg,IDC_STATUS,LB_ADDSTRING,0,lParam);
			SendDlgItemMessage(hdlg,IDC_STATUS,LB_SETTOPINDEX,i,0);
		}
		break;

	case PROGM_START:
		DoImport(hdlg);
		SendMessage(GetParent(hdlg),WIZM_ENABLEBUTTON,1,0);
		SendMessage(GetParent(hdlg),WIZM_ENABLEBUTTON,2,0);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			PostMessage(GetParent(hdlg),WIZM_GOTOPAGE,IDD_FINISHED,(LPARAM)FinishedPageProc);
			break;
		case IDCANCEL:
			PostMessage(GetParent(hdlg),WM_CLOSE,0,0);
			break;
		}
		break;
	}
	return FALSE;
}

void AddMessage( const char* fmt, ... )
{
	va_list args;
	char msgBuf[ 4096 ];
	va_start( args, fmt );

	mir_vsnprintf( msgBuf, sizeof(msgBuf), Translate(fmt), args );

	#ifdef _LOGGING
	{
		FILE *stream;
		stream = fopen("Import Debug.log", "a");
		fprintf(stream, "%s\n", msgBuf);
		fclose(stream);
	}
	#endif

	#if defined( _UNICODE )
	{	TCHAR* str = mir_a2t( msgBuf );
		SendMessage( hdlgProgress, PROGM_ADDMESSAGE, 0, ( LPARAM )str );
		mir_free( str );
	}
	#else
		SendMessage( hdlgProgress, PROGM_ADDMESSAGE, 0, ( LPARAM )msgBuf );
	#endif
}
