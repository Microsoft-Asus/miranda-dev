#ifndef MAIN_H
#define MAIN_H

/*
New_gpg plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Author 
			Copyright (C) 2010-2011 sss

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

struct contact_data
{
	list<string>  msgs_to_send, msgs_to_pass;
	string key_in_prescense;
};

extern std::map<HANDLE, contact_data> hcontact_data;
extern bool bAutoExchange;
extern RECT key_from_keyserver_rect, firstrun_rect, new_key_rect, key_gen_rect, load_key_rect, import_key_rect, key_password_rect, load_existing_key_rect;

#endif


