#ifndef calendar_h
#define calendar_h

/*
Name_day plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Author
			Copyright (C) 2005 Tibor Szabo

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

#include <vector>
#include <string>
using namespace std;

class calendar_t
{
	public:
							calendar_t				(const char *const *const static_names, const size_t names_count, const unsigned icon_id);
							~calendar_t				();
			
			const	string	&get_name				(const unsigned day_in_year) const;
			const	string	&get_name				(const unsigned day, const unsigned month) const;

					unsigned	get_day_in_year		(const unsigned month, const unsigned day) const;
					unsigned	get_name_count		(void) const;



				string				country;
				unsigned			icon_id;

    private:
						calendar_t			() {};

				vector<string>		names;

};


#endif // calendar_h