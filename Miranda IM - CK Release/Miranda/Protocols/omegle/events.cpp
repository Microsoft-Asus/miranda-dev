/*

Omegle plugin for Miranda Instant Messenger
_____________________________________________

Copyright � 2011 Robert P�sel

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "common.h"

int OmegleProto::Log(const char *fmt,...)
{
#ifndef _DEBUG
	return EXIT_SUCCESS;
#endif
	va_list va;
	char text[65535];
	ScopedLock s(log_lock_);

	va_start(va,fmt);
	mir_vsnprintf(text,sizeof(text),fmt,va);
	va_end(va);

	return utils::debug::log( m_szModuleName, text );
}