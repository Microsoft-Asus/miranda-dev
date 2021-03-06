/*
Weather protocol for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright (C) 2005-2011 Boris Krasnovskiy All Rights Reserved
			Copyright (C) 2002-2005 Calvin Che

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

* This file contain the source related to icons info.
*/

#include "weather.h"

HANDLE hIcoLibIconsChanged = NULL;

struct _tag_iconList
{
	char*  szDescr;
	char*  szName;
	int    defIconID;
	HANDLE hIconLibItem;
}
static iconList[] =
{
	{	"Protocol icon",      "main",      IDI_ICON       },
	{	"Update Disabled",    "disabled",  IDI_DISABLED   },
	{	"View Log",           "log",       IDI_LOG        },
	{	"Update with Clear",  "update2",   IDI_UPDATE2    },
	{	"View Brief",         "brief",     IDI_S          },
	{	"View Complete",      "read",      IDI_READ       },
	{	"Weather Update",     "update",    IDI_UPDATE     },
	{	"Weather Map",        "map",       IDI_MAP        },
	{	"Popup",              "popup",     IDI_POPUP      },
	{	"No Popup",           "nopopup",   IDI_NOPOPUP    },
	{	"Edit Settings",      "edit",      IDI_EDIT       },
};

void InitIcons(void)
{
	char szFile[MAX_PATH];
	char szSettingName[100];
	SKINICONDESC sid = {0};
	unsigned i;

	GetModuleFileName(hInst, szFile, MAX_PATH);

	sid.cbSize = sizeof(SKINICONDESC);
	sid.pszDefaultFile = szFile;
	sid.pszName = szSettingName;
	sid.pszSection = WEATHERPROTONAME;

	for (i = 0; i < SIZEOF(iconList); i++) 
	{
		mir_snprintf(szSettingName, sizeof( szSettingName ), "%s_%s", WEATHERPROTONAME, iconList[i].szName);

		sid.pszDescription = iconList[i].szDescr;
		sid.iDefaultIndex = -iconList[i].defIconID;
		iconList[i].hIconLibItem = ( HANDLE )CallService(MS_SKIN2_ADDICON, 0, (LPARAM)&sid);
	}	
}


HICON  LoadIconEx(const char* name, BOOL big)
{
	char szSettingName[100];
	mir_snprintf(szSettingName, sizeof(szSettingName), "%s_%s", WEATHERPROTONAME, name);
	return (HICON)CallService(MS_SKIN2_GETICON, big, (LPARAM)szSettingName);
}

HANDLE  GetIconHandle(const char* name)
{
	unsigned i;
	for (i=0; i < SIZEOF(iconList); i++)
		if (strcmp(iconList[i].szName, name) == 0)
			return iconList[i].hIconLibItem;
	return NULL;
}

void  ReleaseIconEx(HICON hIcon)
{
	CallService(MS_SKIN2_RELEASEICON, (WPARAM)hIcon, 0);
}
