/*
YAMN plugin for 
Miranda IM: the free IM client for Microsoft* Windows*

Author
			Copyright (C) 2002-2004 majvan
			Copyright (C) 2005-2007 tweety y_b

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

* This code implements basics of POP3 protocol

* This was made from the libspopc project copyright c 2002 Benoit Rouits <brouits@free.fr>
* released under the terms of GNU LGPL (GNU Lesser General Public Licence).
* Libspopc offers simple API for a pop3 client (MTA).
* See RFC 1725 for pop3 specifications. More information on http://brouits.free.fr/libspopc/


* This file is not original and is changed by majvan <om3tn@psg.sk> for mail checker purpose.
* Please see original web page to obtain the original. I rewrote it in C++, but good ideas were,
* I think, unchanged.
*
* Note:
* That this file was not designed to work under Unix. It's needed to add Unix-specific features.
  I was interested only in Windows for my project.
*/

#pragma warning( disable : 4290 )

#if !defined(_WIN64)
	#include "../../filter/simple/AggressiveOptimize.h"
#endif
#include <windows.h>
#include <stdio.h>
#include "pop3.h"

extern "C" {
#include "../md5.h"
}

extern void __stdcall	SSL_DebugLog( const char *fmt, ... );

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

//Connects to the server through the netlib
//if not success, exception is throwed
//returns welcome string returned by server
//sets AckFlag
char *CPop3Client::Connect(const char* servername,const int port,BOOL UseSSL, BOOL NoTLS)
{
	char *temp = 0;
	if(Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	if(NetClient!=NULL)
		delete NetClient;
	SSL=UseSSL;
	NetClient=new CNLClient;

#ifdef DEBUG_DECODE
	DebugLog(DecodeFile,"Connect:servername: %s port:%d\n",servername,port);
#endif
	POP3Error=EPOP3_CONNECT;
	NetClient->Connect(servername,port);
	POP3Error=0;

	if (SSL)
	{
		try { NetClient->SSLify(); } 
		catch (...) 
		{
			NetClient->Disconnect();
			return NULL;
		}
	}

	temp = RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	extern BOOL SSLLoaded;
	if (!NoTLS & !(SSL)){
		if(NetClient->Stopped)			//check if we can work with this POP3 client session
			throw POP3Error=(DWORD)EPOP3_STOPPED;
		NetClient->Send("STLS\r\n");
		free(temp);
		temp=RecvRest(NetClient->Recv(),POP3_SEARCHACK);
		if(AckFlag==POP3_FOK){ // Ok, we are going to tls
			try {
				NetClient->SSLify();
			} catch (...) {
				NetClient->Disconnect();
				return NULL;
			}
//			temp = RecvRest(NetClient->Recv(),POP3_SEARCHACK);
		}
	} 
//	SSL_DebugLog("Received: %s",temp);
	return temp;
}

//Receives data to the end of packet
// prev- previous data read (appends to this string next received data)
// mode- mode of packet. 
//       Packet can end with ack state (+OK or -ERR): set mode to POP3_SEARCHACK
//       If packet ends with '.' (end of string), set mode to POP3_SEARCHDOT
// size- received data are stored to memory, but if length of data is more than allocated memory, function allocates
//       new memory. New allocated memory has allocated size more bytes
//       This value can be selectable: if you think it is better to reallocate by 1kB size, select size to 1024,
//       default is 128. You do not need to use this parameter
char* CPop3Client::RecvRest(char* prev,int mode,int size)
{
	int SizeRead=0;
	int SizeLeft=size-NetClient->Rcv;
	int RcvAll=NetClient->Rcv;
	char *LastString,*PrevString=prev;

	AckFlag=0;

	while(((mode==POP3_SEARCHDOT) && !SearchFromEnd(PrevString+RcvAll-1,RcvAll-3,POP3_SEARCHDOT) && !SearchFromStart(PrevString,2,POP3_SEARCHERR)) ||		//we are looking for dot or -err phrase
		((mode==POP3_SEARCHACK) && (!SearchFromStart(PrevString,RcvAll-3,mode) || !((RcvAll>3) && SearchFromEnd(PrevString+RcvAll-1,1,POP3_SEARCHNL)))))			//we are looking for +ok or -err phrase ended with newline
	{		//if not found
		if(NetClient->Stopped)			//check if we can work with this POP3 client session
		{
			if(PrevString!=NULL)
				free(PrevString);
			throw POP3Error=(DWORD)EPOP3_STOPPED;
		}
		if(SizeLeft==0)						//if block is full
		{
			SizeRead+=size;
			SizeLeft=size;
			LastString=NetClient->Recv(NULL,SizeLeft);
			PrevString=(char *)realloc(PrevString,sizeof(char)*(SizeRead+size));
			if(PrevString==NULL)
				throw POP3Error=(DWORD)EPOP3_RESTALLOC;
			memcpy(PrevString+SizeRead,LastString,size);
			free(LastString);
		}
		else
			NetClient->Recv(PrevString+RcvAll,SizeLeft);			//to Rcv stores received bytes
		SizeLeft=SizeLeft-NetClient->Rcv;
		RcvAll+=NetClient->Rcv;
//		printf("[Read: %s]\n",PrevString);
	}
	NetClient->Rcv=RcvAll;			//at the end, store the number of all bytes, no the number of last received bytes
	return PrevString;
}

// CPop3Client::SearchFromEnd
// returns 1 if substring DOTLINE or ENDLINE found from end in bs bytes
// if you need to add condition for mode, insert it into switch statement
BOOL CPop3Client::SearchFromEnd(char *end,int bs,int mode)
{
	while(bs>=0)
	{
		switch(mode)
		{
			case POP3_SEARCHDOT:
				if(DOTLINE(end))
					return 1;
				break;
			case POP3_SEARCHNL:
				if(ENDLINE(end))
					return 1;
				break;
		}
		end--;
		bs--;
	}
	return 0;
}

//Finds for a occurence of some pattern in string
// returns 1 if substring OKLINE, ERRLINE or any of them found from start in bs bytes
//call only this function to retrieve ack status (+OK or -ERR), because it sets flag AckFlag
//if you need to add condition for mode, insert it into switch statement
BOOL CPop3Client::SearchFromStart(char *start,int bs,int mode)
{
	while(bs>=0)
	{
		switch(mode)
		{
			case POP3_SEARCHOK:
				if(OKLINE(start))
				{
					AckFlag=POP3_FOK;
					return 1;
				}
				break;
			case POP3_SEARCHERR:
				if(ERRLINE(start))
				{
					AckFlag=POP3_FERR;
					return 1;
				}
				break;
			case POP3_SEARCHACK:
				if(ACKLINE(start))
				{
					OKLINE(start) ? AckFlag=POP3_FOK : AckFlag=POP3_FERR;
					return 1;
				}
				break;
		}
		start++;
		bs--;
	}
	return 0;
}

//Performs "USER" pop query and returns server response
//sets AckFlag
char* CPop3Client::User(char* name)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];
	char *Result;

	sprintf(query,"USER %s\r\n",name);
	NetClient->Send(query);
	Result=RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	if(AckFlag==POP3_FERR)
		throw POP3Error=(DWORD)EPOP3_BADUSER;
	POP3Error=0;
	return Result;
}

//Performs "PASS" pop query and returns server response
//sets AckFlag
char* CPop3Client::Pass(char* pw)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];
	char *Result;

	sprintf(query,"PASS %s\r\n",pw);
	NetClient->Send(query);
	Result=RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	if(AckFlag==POP3_FERR)
		throw POP3Error=(DWORD)EPOP3_BADPASS;
	return Result;
}

//Performs "APOP" pop query and returns server response
//sets AckFlag
char* CPop3Client::APOP(char* name, char* pw, char* timestamp)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[512];
	char *Result;
	unsigned char digest[16];
	char hexdigest[40];

	if(timestamp==NULL)
		throw POP3Error=(DWORD)EPOP3_APOP;
	MD5Context ctx;
	MD5Init(&ctx);
	MD5Update(&ctx,(const unsigned char *)timestamp,(unsigned int)strlen(timestamp));
	MD5Update(&ctx,(const unsigned char *)pw,(unsigned int)strlen(pw));
	MD5Final(digest,&ctx);
	hexdigest[0]='\0';
	for(int i=0; i<16; i++) {
		char tmp[4];
		sprintf(tmp, "%02x", digest[i]);
		strcat(hexdigest, tmp);
	}
	sprintf(query,"APOP %s %s\r\n",name, hexdigest);
	NetClient->Send(query);
	Result=RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	if(AckFlag==POP3_FERR)
		throw POP3Error=(DWORD)EPOP3_BADUSER;
	return Result;
}

//Performs "QUIT" pop query and returns server response
//sets AckFlag
char* CPop3Client::Quit()
{
	char query[]="QUIT\r\n";

	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHACK);
}

//Performs "STAT" pop query and returns server response
//sets AckFlag
char* CPop3Client::Stat()
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[]="STAT\r\n";

	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHACK);
}

//Performs "LIST" pop query and returns server response
//sets AckFlag
char* CPop3Client::List()
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[]="LIST\r\n";

	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHDOT);
}

//Performs "TOP" pop query and returns server response
//sets AckFlag
char* CPop3Client::Top(int nr, int lines)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];

	sprintf(query,"TOP %d %d\r\n",nr,lines);
	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHDOT);
}

//Performs "UIDL" pop query and returns server response
//sets AckFlag
char* CPop3Client::Uidl(int nr)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];

	if(nr)
	{
		sprintf(query,"UIDL %d\r\n",nr);
		NetClient->Send(query);
		return RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	}
	sprintf(query,"UIDL\r\n");
	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHDOT);
}

//Performs "DELE" pop query and returns server response
//sets AckFlag
char* CPop3Client::Dele(int nr)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];

	sprintf(query,"DELE %d\r\n",nr);
	NetClient->Send(query);
	return RecvRest(NetClient->Recv(),POP3_SEARCHACK);
}
//Performs "RETR" pop query and returns server response
//sets AckFlag
char* CPop3Client::Retr(int nr)
{
	if(NetClient->Stopped)			//check if we can work with this POP3 client session
		throw POP3Error=(DWORD)EPOP3_STOPPED;

	char query[128];

	sprintf(query,"RETR %d\r\n",nr);
	NetClient->Send(query);
	RecvRest(NetClient->Recv(),POP3_SEARCHACK);
	return NetClient->Recv();
}