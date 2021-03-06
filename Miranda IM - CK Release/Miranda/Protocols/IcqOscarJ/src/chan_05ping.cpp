/*
ICQ plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright � 2001-2004 Richard Hughes
			Copyright � 2002-2004 Martin �berg, Sam Kothari, Robert Rainwater
			Copyright � 2004-2010 Joe Kucera, Bio
			Copyright � 2010-2012 Borkra, Georg Hazan

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

#include "icqoscar.h"


void CIcqProto::handlePingChannel(BYTE *buf, WORD datalen)
{
	NetLog_Server("Warning: Ignoring server packet on PING channel");
}


void __cdecl CIcqProto::KeepAliveThread(void *arg)
{
	serverthread_info *info = (serverthread_info*)arg;
	icq_packet packet;
	DWORD dwInterval = getSettingDword(NULL, "KeepAliveInterval", KEEPALIVE_INTERVAL);

	NetLog_Server("Keep alive thread starting.");

	info->hKeepAliveEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	for(;;)
	{
		DWORD dwWait = ICQWaitForSingleObject(info->hKeepAliveEvent, dwInterval);
		if (serverThreadHandle == NULL) // connection lost, end
			break;
		if (dwWait == WAIT_TIMEOUT)
		{
			// Send a keep alive packet to server
			packet.wLen = 0;
			write_flap(&packet, ICQ_PING_CHAN);
			sendServPacket(&packet);
		}
		else if (dwWait == WAIT_IO_COMPLETION)
			// Possible shutdown in progress
			if (Miranda_Terminated()) break;
			else
				break;
	}

	NetLog_Server("Keep alive thread shutting down.");

	CloseHandle(info->hKeepAliveEvent);
	info->hKeepAliveEvent = NULL;
	//
	//info->hKeepAliveEvent = NULL;
	// ^^^ this is not consistent with the SAL annotation on 'CloseHandle'
}


void CIcqProto::StartKeepAlive(serverthread_info *info)
{
	if (info->hKeepAliveEvent) // start only once
		return;

	if (getSettingByte(NULL, "KeepAlive", DEFAULT_KEEPALIVE_ENABLED))
		info->hKeepAliveThread = ForkThreadEx(&CIcqProto::KeepAliveThread, info);
}


void CIcqProto::StopKeepAlive(serverthread_info *info)
{	// finish keep alive thread
	if (info->hKeepAliveEvent)
	{
		SetEvent(info->hKeepAliveEvent);

		// wait for the thread to finish
		ICQWaitForSingleObject(info->hKeepAliveThread, INFINITE, TRUE);
		CloseHandle(info->hKeepAliveThread);
		info->hKeepAliveThread = NULL;
	}
}
