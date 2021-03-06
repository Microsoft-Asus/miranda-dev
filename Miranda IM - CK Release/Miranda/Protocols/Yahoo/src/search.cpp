/*
Yahoo protocol for
Miranda IM: the free IM client for Microsoft* Windows*

Authors 
			Gennady Feldman (aka Gena01) 
			Laurent Marechal (aka Peorth)

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

#include "../yahoo.h"
#include <m_protosvc.h>
#include <m_langpack.h>

#include "resource.h"

////////////////////////////////////////////////////////////////////////////////////////
// SearchBasic - searches the contact by UIN

void __cdecl CYahooProto::search_simplethread(void *snsearch)
{
	TCHAR *id = (TCHAR *) snsearch;

	if (lstrlen(id) < 4) {
		SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, (HANDLE) 1, 0);
		MessageBoxA(NULL, "Please enter a valid ID to search for.", "Search", MB_OK);
		return;
	}

	TCHAR *c = _tcschr(id, '@');
	if (c) *c = 0;

	PROTOSEARCHRESULT psr = { 0 };
	psr.cbSize = sizeof(psr);
	psr.flags = PSR_TCHAR;
	psr.id = (TCHAR*)_tcslwr(id);
	psr.reserved[0] = YAHOO_IM_YAHOO;

	SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_DATA, (HANDLE) 1, (LPARAM) & psr);

	//yahoo_search(m_id, YAHOO_SEARCH_YID, m, YAHOO_GENDER_NONE, YAHOO_AGERANGE_NONE, 0, 1);

	SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, (HANDLE) 1, 0);
}

HANDLE __cdecl CYahooProto::SearchBasic( const TCHAR* nick )
{
	LOG(("[YahooBasicSearch] Searching for: %S", nick));
	
	if ( !m_bLoggedIn )
		return 0;

	YForkThread(&CYahooProto::search_simplethread, _tcsdup( nick ));
	return ( HANDLE )1;
}

////////////////////////////////////////////////////////////////////////////////////////
// SearchAdvanced - searches the contact by UIN

void CYahooProto::ext_got_search_result(int found, int start, int total, YList *contacts)
{
	struct yahoo_found_contact *yct=NULL;
	int i=start;
	YList *en=contacts;

	LOG(("got search result: "));
	
	LOG(("Found: %d", found));
	LOG(("Start: %d", start));
	LOG(("Total: %d", total));
		
	PROTOSEARCHRESULT psr = { 0 };
	psr.cbSize = sizeof(psr);
	psr.flags = PSR_TCHAR;
	psr.reserved[0] = YAHOO_IM_YAHOO;
	
	while (en) {
		yct = ( yahoo_found_contact* )en->data;

		if (yct == NULL) {
			LOG(("[%d] Empty record?",i++));
		} else {
			LOG(("[%d] id: '%s', online: %d, age: %d, sex: '%s', location: '%s'", i++, yct->id, yct->online, yct->age, yct->gender, yct->location));
			psr.id = mir_utf8decodeT( yct->id );
			
			if (yct->gender[0] != 5)
				psr.firstName = mir_utf8decodeT( yct->gender );
			else
				psr.firstName = NULL;
			
			TCHAR c[10];
			if (yct->age > 0) {
				_itot(yct->age, c,10);
				psr.lastName = ( TCHAR* )c;
			}
			else
				psr.lastName = NULL;
			
			if (yct->location[0] != 5)
				psr.email = mir_utf8decodeT( yct->location );
			else
				psr.email = NULL;
	
			//void yahoo_search(int id, enum yahoo_search_type t, const char *text, enum yahoo_search_gender g, enum yahoo_search_agerange ar, 
			//	int photo, int yahoo_only)

			SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_DATA, (HANDLE) 1, (LPARAM) & psr);

			mir_free(psr.id);
			mir_free(psr.firstName);
			mir_free(psr.email);
		}
		en = y_list_next(en);
	}
	SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, (HANDLE) 1, 0);
}

/*
 * This service function creates an advanced search dialog in Find/Add contacts Custom area.
 *
 * Returns: 0 on failure or HWND on success
 */

static INT_PTR CALLBACK YahooSearchAdvancedDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg ) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
			
		SendDlgItemMessageA(hwndDlg, IDC_SEARCH_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)"Yahoo! Messenger");
		SendDlgItemMessageA(hwndDlg, IDC_SEARCH_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)"Lotus Sametime");
		SendDlgItemMessageA(hwndDlg, IDC_SEARCH_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)"LCS");
		SendDlgItemMessageA(hwndDlg, IDC_SEARCH_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)(LPCSTR)"Windows Live (MSN)");
		
		// select the first one
		SendDlgItemMessage(hwndDlg, IDC_SEARCH_PROTOCOL, CB_SETCURSEL, 0, 0);
		return TRUE;
	}
	return FALSE;
}

HWND __cdecl CYahooProto::CreateExtendedSearchUI( HWND parent )
{
	if ( parent && hInstance )
		return CreateDialogParam( hInstance, MAKEINTRESOURCE(IDD_SEARCHUSER), parent, YahooSearchAdvancedDlgProc, ( LPARAM )this );

	return 0;
}

void __cdecl CYahooProto::searchadv_thread(void *pHWND)
{
	HWND hwndDlg = (HWND) pHWND;

	TCHAR searchid[128];
	GetDlgItemText(hwndDlg, IDC_SEARCH_ID, searchid, 128);

	if (lstrlen(searchid) == 0) {
		SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, (HANDLE) 1, 0);
		MessageBoxA(NULL, "Please enter a valid ID to search for.", "Search", MB_OK);
		return;
	} 

	PROTOSEARCHRESULT psr = { 0 };
	psr.cbSize = sizeof(psr);
	psr.flags = PSR_TCHAR;
	psr.id = _tcslwr(searchid);

	int pid = SendDlgItemMessage(hwndDlg , IDC_SEARCH_PROTOCOL, CB_GETCURSEL, 0, 0);
	switch (pid){
		case 0: psr.firstName = _T("<Yahoo >");  pid = YAHOO_IM_YAHOO; break;
		case 1: psr.firstName = _T("<Lotus Sametime>"); pid = YAHOO_IM_SAMETIME;break;
		case 2: psr.firstName = _T("<LCS>"); pid = YAHOO_IM_LCS; break;
		case 3: psr.firstName = _T("<Windows Live (MSN)>"); pid = YAHOO_IM_MSN; break;
	}

	psr.reserved[0] = pid;

	/*
	* Show this in results
	*/
	SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_DATA, (HANDLE) 1, (LPARAM) & psr);

	/*
	* Done searching.
	*/
	SendBroadcast(NULL, ACKTYPE_SEARCH, ACKRESULT_SUCCESS, (HANDLE) 1, 0);
}

/*
 * This service function does the advanced search
 *
 * Returns: 0 on failure or HWND on success
 */

HWND __cdecl CYahooProto::SearchAdvanced( HWND owner )
{
	LOG(("[YahooAdvancedSearch]"));

	if ( !m_bLoggedIn )
		return 0;

	YForkThread( &CYahooProto::searchadv_thread, owner );
	return ( HWND )1;
}
