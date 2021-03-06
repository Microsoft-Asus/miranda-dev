/*
ListeningTo plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
                Copyright (C) 2005-2011 Ricardo Pescuma Domenecci
                          (C) 2010-2011 Merlin_de

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

#include "commons.h"

extern int activePlayer;

Player *players[NUM_PLAYERS];
static LISTENINGTOINFO current = {0};

void InitMusic() 
{
	players[WATRACK]	= new WATrack(WATRACK);
	players[GENERIC]	= new GenericPlayer(GENERIC);
	players[WMP]		= new WindowsMediaPlayer(WMP);
	players[WLM]		= new WindowsLiveMessanger(WLM);
	players[WINAMP]		= new Winamp(WINAMP);
	players[ITUNES]		= new ITunes(ITUNES);
	players[FOOBAR]		= new Foobar(FOOBAR);
	players[MRADIO]		= new mRadio(MRADIO);
//	players[VIDEOLAN]	= new VideoLAN(VIDEOLAN);
}


void FreeMusic()
{
	for(int i = 0; i < NUM_PLAYERS; i++)
	{
		delete players[i];
		players[i] = NULL;
	}
}


void EnableDisablePlayers()
{
	for(int i = 0; i < NUM_PLAYERS; i++)
		players[i]->EnableDisable();
}

void FreeListeningInfo(LISTENINGTOINFO *lti)
{
	if(!lti)
		lti = &current;
	lti->cbSize = 0;
	lti->dwFlags = 0;
	MIR_FREE(lti->ptszArtist);
	MIR_FREE(lti->ptszAlbum);
	MIR_FREE(lti->ptszTitle);
	MIR_FREE(lti->ptszTrack);
	MIR_FREE(lti->ptszYear);
	MIR_FREE(lti->ptszGenre);
	MIR_FREE(lti->ptszLength);
	MIR_FREE(lti->ptszPlayer);
	MIR_FREE(lti->ptszType);
}

void CopyListeningInfo(LISTENINGTOINFO *dest, const LISTENINGTOINFO * const src)
{
	FreeListeningInfo(dest);

	dest->cbSize = src->cbSize;
	dest->dwFlags = src->dwFlags;
	dest->ptszArtist = mir_tstrdup(src->ptszArtist);
	dest->ptszAlbum = mir_tstrdup(src->ptszAlbum);
	dest->ptszTitle = mir_tstrdup(src->ptszTitle);
	dest->ptszTrack = mir_tstrdup(src->ptszTrack);
	dest->ptszYear = mir_tstrdup(src->ptszYear);
	dest->ptszGenre = mir_tstrdup(src->ptszGenre);
	dest->ptszLength = mir_tstrdup(src->ptszLength);
	dest->ptszPlayer = mir_tstrdup(src->ptszPlayer);
	dest->ptszType = mir_tstrdup(src->ptszType);
}

BOOL Equals(const LISTENINGTOINFO *lti1, const LISTENINGTOINFO *lti2)
{
	if (lti1->cbSize != lti2->cbSize)
		return FALSE;

	return lstrcmpi(lti1->ptszArtist, lti2->ptszArtist) == 0 
		&& lstrcmpi(lti1->ptszAlbum, lti2->ptszAlbum) == 0 
		&& lstrcmpi(lti1->ptszTitle, lti2->ptszTitle) == 0 
		&& lstrcmpi(lti1->ptszTrack, lti2->ptszTrack) == 0 
		&& lstrcmpi(lti1->ptszYear, lti2->ptszYear) == 0 
		&& lstrcmpi(lti1->ptszGenre, lti2->ptszGenre) == 0 
		&& lstrcmpi(lti1->ptszLength, lti2->ptszLength) == 0 
		&& lstrcmpi(lti1->ptszPlayer, lti2->ptszPlayer) == 0 
		&& lstrcmpi(lti1->ptszType, lti2->ptszType) == 0;
}


int ChangedListeningInfo()
{
//	m_log(_T("ChangedListeningInfo"), _T("Start"));

	int first, last;
	BOOL changed = FALSE;
	BOOL playing = FALSE;

	if(activePlayer > -1 && players[activePlayer]->GetStatus() > PL_OFFLINE) {
		first = activePlayer;
		last  = activePlayer +1;
	}
	else {
		activePlayer = -1;
		first = (players[WATRACK]->m_enabled ? WATRACK : GENERIC);
		last  = (players[WATRACK]->m_enabled ? WATRACK + 1 : NUM_PLAYERS);
	}

	for (int i = first; i < last; i++) 
	{
		if (!players[i]->m_enabled)
			continue;

		if (activePlayer == -1 && !players[i]->GetStatus())		//player is offline
			continue;

		LISTENINGTOINFO lti = {0};
		if (!players[i]->GetListeningInfo(&lti))
			continue;

		if (!IsTypeEnabled(&lti)) //Music, Radio, Video ?
		{
			FreeListeningInfo(&lti);
			continue;
		}

		playing = TRUE;
		activePlayer = i;

//		m_log(_T("ChangedListeningInfo"), _T("Has : %s : %d"), players[i]->name, lti.cbSize);

		if (Equals(&current, &lti))
		{
//			m_log(_T("ChangedListeningInfo"), _T("Is equals"));
			FreeListeningInfo(&lti);
		}
		else
		{
//			m_log(_T("ChangedListeningInfo"), _T("Is different"));

			FreeListeningInfo(&current);

			memmove(&current, &lti, sizeof(current));

			changed = 1;
		}

		break;
	} //end for

	if (!playing && current.cbSize != 0)
	{
		FreeListeningInfo(&current);
		changed = 1;
	}

	if (!changed)
		return 0;
	else
		return current.cbSize == 0 ? -1 : 1;
}


LISTENINGTOINFO * GetListeningInfo()
{
	if (current.cbSize == 0)
		return NULL;

	return &current;
}
