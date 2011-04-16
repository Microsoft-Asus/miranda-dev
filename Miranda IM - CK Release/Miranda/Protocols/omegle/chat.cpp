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

void OmegleProto::UpdateChat(const char *name, const char *message, bool addtolog)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);

	GCEVENT gce  = {sizeof(gce)};
	gce.pDest    = &gcd;
	gce.bIsMe    = (name == "You");
	gce.ptszText = mir_a2t_cp(message,CP_UTF8);
	gce.time     = ::time(NULL);
	gce.dwFlags  = GC_TCHAR;

	if (name == NULL) {
		gcd.iType  = GC_EVENT_INFORMATION;
		name = "Server";
	} else {
		gcd.iType  = GC_EVENT_MESSAGE;
		gce.dwFlags  |= GCEF_ADDTOLOG;
	}

	if (addtolog)
		gce.dwFlags  |= GCEF_ADDTOLOG;

	gce.ptszNick = mir_a2t(Translate(name));
	gce.ptszUID  = gce.ptszNick;

	CallServiceSync(MS_GC_EVENT,0,reinterpret_cast<LPARAM>(&gce));

	mir_free(const_cast<TCHAR*>(gce.ptszNick));
	mir_free(const_cast<TCHAR*>(gce.ptszText));
}

int OmegleProto::OnChatOutgoing(WPARAM wParam,LPARAM lParam)
{
	GCHOOK *hook = reinterpret_cast<GCHOOK*>(lParam);
	char *text;

	if(strcmp(hook->pDest->pszModule,m_szModuleName))
		return 0;

	switch(hook->pDest->iType)
	{
	case GC_USER_MESSAGE:
	{
		text = mir_t2a_cp(hook->ptszText,CP_UTF8);

		std::string* response_data = new std::string(text);
	
		if (*response_data == "/new")
			NewChat();
		else if (*response_data == "/quit")
			StopChat();
		else {
			if ( facy.connected_ ) {

				DBVARIANT dbv;
				if (*response_data == "/asl") {
					*response_data = "";
					if ( !getU8String( OMEGLE_KEY_ASL,&dbv ) ) {
						*response_data = dbv.pszVal;
						DBFreeVariant(&dbv);
					}
				} /*else if (*response_data == "/hi") {
					*response_data = "";
					if ( !getU8String( OMEGLE_KEY_HI,&dbv ) ) {
						*response_data = dbv.pszVal;
						DBFreeVariant(&dbv);
					}
				}*/

				LOG("**Chat - Outgoing message: %s", response_data->c_str());
				ForkThread(&OmegleProto::SendMsgWorker, this, (void*)response_data);
			} else {
				UpdateChat(NULL, Translate("First you have to connect to some Stranger by sending '/new' message. You can use this to change actual Stranger during conversation too. Send '/quit' message if you want to end conversation."));
			}
		}
	
		break;
	}

	case GC_USER_LEAVE:
	case GC_SESSION_TERMINATE:
	{
		StopChat();
		break;
	}
  }

	return 0;
}

/*void OmegleProto::SendChatEvent(int type)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType = GC_EVENT_CONTROL;

	GCEVENT gce = {sizeof(gce)};
	gce.dwFlags = GC_TCHAR;
	gce.pDest = &gcd;

	CallServiceSync(MS_GC_EVENT,WINDOW_CLEARLOG,reinterpret_cast<LPARAM>(&gce));
}*/

void OmegleProto::AddChatContact(const char *name)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType  = GC_EVENT_JOIN;

	GCEVENT gce    = {sizeof(gce)};
	gce.pDest      = &gcd;
	gce.dwFlags    = GC_TCHAR;
	gce.ptszNick   = mir_a2t(Translate(name));
	gce.ptszUID    = gce.ptszNick;
	gce.bIsMe      = (name == "You");
	gce.ptszStatus = _T("Normal");
	gce.time       = static_cast<DWORD>(time(0));
	
	gce.dwFlags  |= GCEF_ADDTOLOG;

	CallServiceSync(MS_GC_EVENT,0,reinterpret_cast<LPARAM>(&gce));

	mir_free(const_cast<TCHAR*>(gce.ptszNick));
}

void OmegleProto::DeleteChatContact(const char *name)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType  = GC_EVENT_PART;

	GCEVENT gce    = {sizeof(gce)};
	gce.pDest      = &gcd;
	gce.dwFlags    = GC_TCHAR;
	gce.ptszNick   = mir_a2t(Translate(name));
	gce.ptszUID    = gce.ptszNick;
	gce.time       = static_cast<DWORD>(time(0));

	gce.dwFlags  |= GCEF_ADDTOLOG;

	CallServiceSync(MS_GC_EVENT,0,reinterpret_cast<LPARAM>(&gce));

	mir_free(const_cast<TCHAR*>(gce.ptszNick));
}

int OmegleProto::OnJoinChat(WPARAM,LPARAM suppress)
{	
	GCSESSION gcw = {sizeof(gcw)};

	// Create the group chat session
	gcw.dwFlags   = GC_TCHAR;
	gcw.iType     = GCW_CHATROOM;
	gcw.pszModule = m_szModuleName;
	gcw.ptszName  = m_tszUserName;
	gcw.ptszID    = m_tszUserName;
	CallServiceSync(MS_GC_NEWSESSION, 0, (LPARAM)&gcw);

	if(m_iStatus != ID_STATUS_ONLINE)
		return 0;

	// Create a group
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);

	GCEVENT gce = {sizeof(gce)};
	gce.pDest = &gcd;
	gce.dwFlags = GC_TCHAR;

	gcd.iType = GC_EVENT_ADDGROUP;
	gce.ptszStatus = _T("Normal");
	CallServiceSync(MS_GC_EVENT,0,reinterpret_cast<LPARAM>(&gce));


	// Set topic
	gcd.iType = GC_EVENT_TOPIC;
	gce.time = ::time(NULL);
	gce.ptszText = _T("Omegle is a great way of meeting new friends!");
	CallServiceSync(MS_GC_EVENT,0,  reinterpret_cast<LPARAM>(&gce));

	// Note: Initialization will finish up in SetChatStatus, called separately
	if(!suppress)
		SetChatStatus(m_iStatus);

	return 0;
}

int OmegleProto::OnLeaveChat(WPARAM,LPARAM)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType = GC_EVENT_CONTROL;

	GCEVENT gce = {sizeof(gce)};
	gce.dwFlags = GC_TCHAR;
	gce.time = ::time(NULL);
	gce.pDest = &gcd;

	CallServiceSync(MS_GC_EVENT,SESSION_OFFLINE,  reinterpret_cast<LPARAM>(&gce));
	CallServiceSync(MS_GC_EVENT,SESSION_TERMINATE,reinterpret_cast<LPARAM>(&gce));

	return 0;
}

void OmegleProto::SetChatStatus(int status)
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType = GC_EVENT_CONTROL;

	GCEVENT gce = {sizeof(gce)};
	gce.dwFlags = GC_TCHAR;
	gce.time = ::time(NULL);
	gce.pDest = &gcd;

	if(status == ID_STATUS_ONLINE)
	{
		
		DBVARIANT dbv;
		if ( !getU8String( OMEGLE_KEY_NAME,&dbv ) ) {
			AddChatContact(dbv.pszVal);
			DBFreeVariant(&dbv);
		} else {
			AddChatContact("You");
		}

		CallServiceSync(MS_GC_EVENT,SESSION_INITDONE,reinterpret_cast<LPARAM>(&gce));
		CallServiceSync(MS_GC_EVENT,SESSION_ONLINE,  reinterpret_cast<LPARAM>(&gce));
	}
	else
	{
		CallServiceSync(MS_GC_EVENT,SESSION_OFFLINE,reinterpret_cast<LPARAM>(&gce));
	}
}

void OmegleProto::ClearChat()
{
	GCDEST gcd = { m_szModuleName };
	gcd.ptszID = const_cast<TCHAR*>(m_tszUserName);
	gcd.iType = GC_EVENT_CONTROL;

	GCEVENT gce = {sizeof(gce)};
	gce.dwFlags = GC_TCHAR;
	gce.pDest = &gcd;

	CallServiceSync(MS_GC_EVENT,WINDOW_CLEARLOG,reinterpret_cast<LPARAM>(&gce));
}