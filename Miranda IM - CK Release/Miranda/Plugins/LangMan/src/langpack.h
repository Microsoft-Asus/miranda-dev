/*
Language Pack Manager plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Author
			Copyright (C) 2005-2012 H. Herkenrath

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

/* Langpack Info */
typedef struct {
	TCHAR szLanguage[64];
	LCID Locale;
	WORD codepage;
	char szAuthors[1024];
	char szAuthorEmail[128];
	char szLastModifiedUsing[64];
	char szPluginsIncluded[4080];
	char szVersion[21];
	char szFLName[128];
	FILETIME ftFileDate;
	TCHAR szFileName[MAX_PATH]; /* just the file name itself */
	BYTE flags; /* see LPIF_* flags */
} LANGPACK_INFO;
#define LPF_ENABLED   0x01  // pack is enabled
#define LPF_NOLOCALE  0x02  // pack has no valid locale
#define LPF_DEFAULT   0x04  // pack is the english default (no langpack)

/* Enum */
BOOL GetPackPath(TCHAR *pszPath,int nSize,BOOL fEnabledPacks,const TCHAR *pszFile);
typedef BOOL (*ENUM_PACKS_CALLBACK)(LANGPACK_INFO *pack,WPARAM wParam,LPARAM lParam);
BOOL EnumPacks(ENUM_PACKS_CALLBACK callback,const TCHAR *pszFilePattern,const char *pszFileVersionHeader,BOOL fEnglishDefault,WPARAM wParam,LPARAM lParam);
BOOL IsPluginIncluded(const LANGPACK_INFO *pack,char *pszFileBaseName);

/* Switch */
BOOL EnablePack(const LANGPACK_INFO *pack,const TCHAR *pszFilePattern);
void CorrectPacks(const TCHAR *pszFilePattern,BOOL fDisableAll);
