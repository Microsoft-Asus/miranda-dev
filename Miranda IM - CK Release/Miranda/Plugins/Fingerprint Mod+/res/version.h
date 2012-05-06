/*
Fingerprint Mod+ (client version) for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
Copyright (C) 2006-2007 Artem Shpynov aka FYR, Bio
						Faith Healer
			  2009-2010 HierOS
			  2011-2012 Mataes

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

#define __MAJOR_VERSION				0
#define __MINOR_VERSION				2
#define __RELEASE_NUM				2
#define __BUILD_NUM					4

#define __FILEVERSION_STRING        __MAJOR_VERSION,__MINOR_VERSION,__RELEASE_NUM,__BUILD_NUM
#define __FILEVERSION_DOTS			__MAJOR_VERSION.__MINOR_VERSION.__RELEASE_NUM.__BUILD_NUM

#define __STRINGIFY_IMPL(x)			#x
#define __STRINGIFY(x)				__STRINGIFY_IMPL(x)
#define __VERSION_STRING			__STRINGIFY(__FILEVERSION_DOTS)
#define __VERSION_DWORD             PLUGIN_MAKE_VERSION(__MAJOR_VERSION, __MINOR_VERSION, __RELEASE_NUM, __BUILD_NUM)

#ifdef _UNICODE
#ifdef _WIN64
#define __INTERNAL_NAME_STRING "Fingerprint Mod+ (x64)"
#define __PLUGIN_ID 4302
#define __PLUGIN_ID_STR "4302"
#define __BETA_FILE_TITLE "fingerprint_x64"
#else //!_WIN64
#define __INTERNAL_NAME_STRING "Fingerprint Mod+ (Unicode)"
#define __PLUGIN_ID 4301
#define __PLUGIN_ID_STR "4301"
#define __BETA_FILE_TITLE "fingerprint_unicode"
#endif //_WIN64
#else //!_UNICODE
#define __INTERNAL_NAME_STRING "Fingerprint Mod+"
#define __PLUGIN_ID 4300
#define __PLUGIN_ID_STR "4300"
#define __BETA_FILE_TITLE "fingerprint"
#endif //_UNICODE

#define __LEGAL_COPYRIGHT_STRING "�2009-2010 HierOS, �2006-2007 Artem Shpynov aka FYR, Bio, Faith Healer."

// Fingerprint interface ID. Should be the same for ALL fingerprint plugins.
// {FFF4B77A-CE40-11DB-A5CD-06A755D89593}
#define MIID_FINGERPRINT	{0xFFF4B77A, 0xCE40, 0x11DB, { 0xA5, 0xCD, 0x06, 0xA7, 0x55, 0xD8, 0x95, 0x93}}
#define MIID_THIS_PLUGIN	{0x687364af, 0x58b0, 0x4af2, { 0xa4, 0xee, 0x20, 0xf4, 0xa,  0x8d, 0x9a, 0xfb}}
