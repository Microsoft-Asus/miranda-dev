/*
Nudge plugin for 
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright (C)	francois.mean@skynet.be
							Sylvain.gougouzian@gmail.com
							wishmaster51@googlemail.com

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

#include "headers.h"
#include "main.h"
#include "shake.h"
#include "options.h"

CNudgeElement* ActualNudge = NULL;



int NudgeOptInit(WPARAM wParam,LPARAM lParam)
{
	OPTIONSDIALOGPAGE odp = { 0 };
	odp.cbSize						= sizeof(odp);
	odp.position					= -790000000;
	odp.hInstance					= hInst;
	odp.pszTemplate					= MAKEINTRESOURCEA(IDD_OPT_NUDGE);
	odp.ptszTitle					= LPGENT("Nudge");
	odp.ptszGroup					= LPGENT("Events");
	odp.ptszTab						= LPGENT("Nudge");
	odp.flags						= ODPF_BOLDGROUPS|ODPF_TCHAR;
//	odp.nIDBottomSimpleControl = IDC_STMSNGROUP;
	odp.pfnDlgProc					= DlgProcNudgeOpt;
	CallService( MS_OPT_ADDPAGE, wParam,( LPARAM )&odp );

	odp.position					= -790000001;
	odp.ptszTab						= LPGENT("Window Shaking");
	odp.pfnDlgProc					= DlgProcShakeOpt;
	odp.flags |= ODPF_EXPERTONLY;
	odp.pszTemplate					= MAKEINTRESOURCEA(IDD_OPT_SHAKE);
	CallService( MS_OPT_ADDPAGE, wParam,( LPARAM )&odp );
	return 0;
}

INT_PTR CALLBACK DlgProcShakeOpt(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
			TCHAR szBuf[20];
			TranslateDialogDefault(hwnd);
			mir_sntprintf(szBuf, 10, _T("%d"), shake.nMoveClist);
			SetDlgItemText(hwnd,IDC_LNUMBER_CLIST,szBuf);
			mir_sntprintf(szBuf, 10, _T("%d"), shake.nMoveChat);
			SetDlgItemText(hwnd,IDC_LNUMBER_CHAT,szBuf);

			mir_sntprintf(szBuf, 10, _T("%d"), shake.nScaleClist);
			SetDlgItemText(hwnd,IDC_LSCALE_CLIST,szBuf);
			mir_sntprintf(szBuf, 10, _T("%d"), shake.nScaleChat);
			SetDlgItemText(hwnd,IDC_LSCALE_CHAT,szBuf);

			SendDlgItemMessage(hwnd, IDC_SNUMBER_CLIST, TBM_SETRANGE, 0, (LPARAM)MAKELONG(1, 60));
			SendDlgItemMessage(hwnd, IDC_SNUMBER_CHAT, TBM_SETRANGE, 0, (LPARAM)MAKELONG(1, 60));

			SendDlgItemMessage(hwnd, IDC_SSCALE_CLIST, TBM_SETRANGE, 0, (LPARAM)MAKELONG(1, 40));
			SendDlgItemMessage(hwnd, IDC_SSCALE_CHAT, TBM_SETRANGE, 0, (LPARAM)MAKELONG(1, 40));

			SendDlgItemMessage(hwnd, IDC_SNUMBER_CLIST, TBM_SETPOS, TRUE, shake.nMoveClist);
			SendDlgItemMessage(hwnd, IDC_SNUMBER_CHAT, TBM_SETPOS, TRUE, shake.nMoveChat);

			SendDlgItemMessage(hwnd, IDC_SSCALE_CLIST, TBM_SETPOS, TRUE, shake.nScaleClist);
			SendDlgItemMessage(hwnd, IDC_SSCALE_CHAT, TBM_SETPOS, TRUE, shake.nScaleChat);

			break;
		case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam);
			switch(LOWORD(wParam))
			{
				case IDC_PREVIEW:
					ShakeClist(0,0);
					//SendMessage(GetParent(hwnd),PSM_CHANGED,0,0);
					break;
			}
			break;
		}
		case WM_HSCROLL:
            if((HWND)lParam == GetDlgItem(hwnd, IDC_SNUMBER_CLIST) || (HWND)lParam == GetDlgItem(hwnd, IDC_SNUMBER_CHAT) 
				|| (HWND)lParam == GetDlgItem(hwnd, IDC_SSCALE_CLIST) || (HWND)lParam == GetDlgItem(hwnd, IDC_SSCALE_CHAT)) 
			{
                TCHAR szBuf[20];
                DWORD dwPos = SendMessage((HWND) lParam, TBM_GETPOS, 0, 0);
                mir_sntprintf(szBuf, sizeof(szBuf), _T("%d"), dwPos);
                if ((HWND)lParam == GetDlgItem(hwnd, IDC_SNUMBER_CLIST))
					SetDlgItemText(hwnd,IDC_LNUMBER_CLIST,szBuf);
                if ((HWND)lParam == GetDlgItem(hwnd, IDC_SNUMBER_CHAT))
					SetDlgItemText(hwnd,IDC_LNUMBER_CHAT,szBuf);
				if ((HWND)lParam == GetDlgItem(hwnd, IDC_SSCALE_CLIST))
					SetDlgItemText(hwnd,IDC_LSCALE_CLIST,szBuf);
                if ((HWND)lParam == GetDlgItem(hwnd, IDC_SSCALE_CHAT))
					SetDlgItemText(hwnd,IDC_LSCALE_CHAT,szBuf);
                SendMessage(GetParent(hwnd), PSM_CHANGED, 0, 0);
            }
			break;

		case WM_SHOWWINDOW:
			break;

		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->idFrom)
			{
				case 0:
					switch(((LPNMHDR)lParam)->code)
					{
						case PSN_APPLY:
						{
							shake.nMoveClist = (int) SendMessage(GetDlgItem(hwnd, IDC_SNUMBER_CLIST), TBM_GETPOS, 0, 0);
							shake.nMoveChat = (int) SendMessage(GetDlgItem(hwnd, IDC_SNUMBER_CHAT), TBM_GETPOS, 0, 0);
							shake.nScaleClist = (int) SendMessage(GetDlgItem(hwnd, IDC_SSCALE_CLIST), TBM_GETPOS, 0, 0);
							shake.nScaleChat = (int) SendMessage(GetDlgItem(hwnd, IDC_SSCALE_CHAT), TBM_GETPOS, 0, 0);
							shake.Save();
						}
					}
			}
			break;
	}

	return FALSE;
}

void CreateImageList(HWND hWnd)
{
	// Create and populate image list
	HIMAGELIST hImList = ImageList_Create(GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),	ILC_MASK | ILC_COLOR32, nProtocol, 0);

	for(NudgeElementList *n = NudgeList;n != NULL; n = n->next)
	{
		INT_PTR res = CallProtoService(n->item.ProtocolName, PS_LOADICON,PLI_PROTOCOL | PLIF_SMALL | PLIF_ICOLIB, 0);
		if(res==CALLSERVICE_NOTFOUND)
		{
			res = CallService(MS_SKIN2_GETICONBYHANDLE,0,(LPARAM)n->item.hIcoLibItem);
		}

		HICON hIcon = (HICON) res;
		ImageList_AddIcon(hImList, hIcon);
	}
	//ADD default Icon for nudge
	HICON hIcon = (HICON) LoadImage(hInst, MAKEINTRESOURCE(IDI_NUDGE), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), 0);
	ImageList_AddIcon(hImList, hIcon);
	DestroyIcon(hIcon);

	HWND hLstView = GetDlgItem(hWnd, IDC_PROTOLIST);
	TreeView_SetImageList(hLstView, hImList, TVSIL_NORMAL);
}

void PopulateProtocolList(HWND hWnd)
{
	bool useOne = IsDlgButtonChecked(hWnd, IDC_USEBYPROTOCOL) == BST_UNCHECKED;

	HWND hLstView = GetDlgItem(hWnd, IDC_PROTOLIST);

	TreeView_DeleteAllItems(hLstView);

	TVINSERTSTRUCT tvi = {0};
	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_STATE | TVIF_SELECTEDIMAGE;
	tvi.item.stateMask = TVIS_STATEIMAGEMASK;

	int i = 0;
	if (GlobalNudge.useByProtocol)
	{
		for(NudgeElementList *n = NudgeList;n != NULL; n = n->next)
		{
			tvi.item.pszText = n->item.AccountName;
			tvi.item.iImage  = i;
			n->item.iProtoNumber = i;
			tvi.item.iSelectedImage = i;
			tvi.item.state = INDEXTOSTATEIMAGEMASK(n->item.enabled?2:1);	
			TreeView_InsertItem(hLstView, &tvi);
			i++;
		}
	}
	else
	{
		tvi.item.pszText = TranslateT("Nudge");
		tvi.item.iImage  = nProtocol;
		DefaultNudge.iProtoNumber = nProtocol;
		tvi.item.iSelectedImage = nProtocol;
		tvi.item.state = INDEXTOSTATEIMAGEMASK(DefaultNudge.enabled?2:1);	
		TreeView_InsertItem(hLstView, &tvi);

	}
	TreeView_SelectItem(hLstView, TreeView_GetRoot(hLstView));
	//TreeView_SetCheckState(hLstView, TreeView_GetRoot(hLstView), TRUE)
}


INT_PTR CALLBACK DlgProcNudgeOpt(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static bool iInitDone = true;
	switch(msg)
	{
		case WM_INITDIALOG:
			iInitDone = false;
			TranslateDialogDefault(hwnd);
			CreateImageList(hwnd);
			PopulateProtocolList(hwnd);
			UpdateControls(hwnd);
			iInitDone = true;
			break;
		case WM_DESTROY:
		{
			HIMAGELIST hImList = TreeView_GetImageList(GetDlgItem(hwnd, IDC_PROTOLIST), TVSIL_NORMAL);
			if (hImList)
			{
				TreeView_SetImageList(GetDlgItem(hwnd, IDC_PROTOLIST), NULL, TVSIL_NORMAL); // Avoiding Access Violation in CommonControls DLL
				ImageList_Destroy(hImList);
			}
			break;
		}
		case WM_COMMAND:
		{
			WORD wNotifyCode = HIWORD(wParam);
			switch(LOWORD(wParam))
			{
				case IDC_PREVIEW:
					Preview();
					break;
				case IDC_USEBYPROTOCOL:
					GlobalNudge.useByProtocol = (IsDlgButtonChecked(hwnd,IDC_USEBYPROTOCOL)==BST_CHECKED);
					PopulateProtocolList(hwnd);
					UpdateControls(hwnd);
					SendMessage(GetParent(hwnd),PSM_CHANGED,0,0);
					break;
				case IDC_AUTORESEND:
					if (ActualNudge)// fix NULL pointer then no nudge support protocols
					{
						ActualNudge->autoResend = (IsDlgButtonChecked(hwnd,IDC_AUTORESEND)==BST_CHECKED);
						EnableWindow(GetDlgItem(hwnd,IDC_RESENDDELAY),ActualNudge->autoResend);						
					}
					SendMessage(GetParent(hwnd),PSM_CHANGED,0,0);
					break;
				case IDC_CHECKST0:
				case IDC_CHECKST1:
				case IDC_CHECKST2:
				case IDC_CHECKST3:
				case IDC_CHECKST4:
				case IDC_CHECKST5:
				case IDC_CHECKST6:
				case IDC_CHECKST7:
				case IDC_CHECKST8:
				case IDC_CHECKST9:
				case IDC_CHECKPOP:
				case IDC_OPENMESSAGE:
				case IDC_CHECKCLIST:
				case IDC_CHECKCHAT:
				case IDC_CHECKSTATUS:
				case IDC_IGNORE:
				case IDC_OPENCONTACTLIST:
					SendMessage(GetParent(hwnd),PSM_CHANGED,0,0);
					break;
				case IDC_RESENDDELAY:
				case IDC_SENDTEXT:
				case IDC_RECVTEXT:
				case IDC_SENDTIME:
				case IDC_RECVTIME:
					if(iInitDone && (wNotifyCode == EN_CHANGE))
						SendMessage(GetParent(hwnd),PSM_CHANGED,0,0);
					break;
			}
			break;
		}
		case WM_SHOWWINDOW:
			break;

		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->idFrom)
			{
				case 0:
					switch(((LPNMHDR)lParam)->code)
					{
						case PSN_APPLY:
						{
							BOOL Translated;
							GlobalNudge.sendTimeSec = GetDlgItemInt(hwnd,IDC_SENDTIME,&Translated,FALSE);
							GlobalNudge.recvTimeSec  = GetDlgItemInt(hwnd,IDC_RECVTIME,&Translated,FALSE);
							GlobalNudge.resendDelaySec  = GetDlgItemInt(hwnd,IDC_RESENDDELAY,&Translated,FALSE);
							if(GlobalNudge.resendDelaySec > 10 ) GlobalNudge.resendDelaySec = 10; 
							if(GlobalNudge.resendDelaySec < 1 ) GlobalNudge.resendDelaySec = 1;
							if (ActualNudge)// fix NULL pointer then no nudge support protocols
							{
								ActualNudge->shakeClist = (IsDlgButtonChecked(hwnd,IDC_CHECKCLIST)==BST_CHECKED);
								ActualNudge->shakeChat = (IsDlgButtonChecked(hwnd,IDC_CHECKCHAT)==BST_CHECKED);
								ActualNudge->openMessageWindow = (IsDlgButtonChecked(hwnd,IDC_OPENMESSAGE)==BST_CHECKED);
								ActualNudge->openContactList = (IsDlgButtonChecked(hwnd,IDC_OPENCONTACTLIST)==BST_CHECKED);
								ActualNudge->useIgnoreSettings = (IsDlgButtonChecked(hwnd,IDC_IGNORE)==BST_CHECKED);
								ActualNudge->showStatus = (IsDlgButtonChecked(hwnd,IDC_CHECKSTATUS)==BST_CHECKED);
								ActualNudge->showPopup = (IsDlgButtonChecked(hwnd,IDC_CHECKPOP)==BST_CHECKED);
								ActualNudge->statusFlags =
										((IsDlgButtonChecked(hwnd,IDC_CHECKST0)==BST_CHECKED) ? NUDGE_ACC_ST0 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST1)==BST_CHECKED) ? NUDGE_ACC_ST1 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST2)==BST_CHECKED) ? NUDGE_ACC_ST2 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST3)==BST_CHECKED) ? NUDGE_ACC_ST3 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST4)==BST_CHECKED) ? NUDGE_ACC_ST4 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST5)==BST_CHECKED) ? NUDGE_ACC_ST5 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST6)==BST_CHECKED) ? NUDGE_ACC_ST6 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST7)==BST_CHECKED) ? NUDGE_ACC_ST7 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST8)==BST_CHECKED) ? NUDGE_ACC_ST8 : 0) |
										((IsDlgButtonChecked(hwnd,IDC_CHECKST9)==BST_CHECKED) ? NUDGE_ACC_ST9 : 0) ;

								GetDlgItemText(hwnd,IDC_SENDTEXT,ActualNudge->senText,TEXT_LEN);
								GetDlgItemText(hwnd,IDC_RECVTEXT,ActualNudge->recText,TEXT_LEN);
								ActualNudge->Save();
							}
							GlobalNudge.Save();
						}
					}
				case IDC_PROTOLIST:
					switch (((LPNMHDR)lParam)->code)
					{
						case NM_CLICK:
							{
								TVHITTESTINFO ht = {0};

								DWORD dwpos = GetMessagePos();
								POINTSTOPOINT(ht.pt, MAKEPOINTS(dwpos));
								MapWindowPoints(HWND_DESKTOP, ((LPNMHDR)lParam)->hwndFrom, &ht.pt, 1);

								TreeView_HitTest(((LPNMHDR)lParam)->hwndFrom, &ht);
								/*if (TVHT_ONITEM & ht.flags)
									CheckChange(hwnd,ht.hItem);*/
								if (TVHT_ONITEMSTATEICON & ht.flags)
									CheckChange(hwnd,ht.hItem);
							}

						case TVN_KEYDOWN:
							 if (((LPNMTVKEYDOWN) lParam)->wVKey == VK_SPACE)
									CheckChange(hwnd, TreeView_GetSelection(((LPNMHDR)lParam)->hwndFrom));
							break;

						case TVN_SELCHANGED:
							{
								LPNMTREEVIEW pnmtv = (LPNMTREEVIEW) lParam;
								if (pnmtv->itemNew.state & TVIS_SELECTED)
									UpdateControls(hwnd);
							}
							break;
					}
					break;
			}
			break;
	}

	return FALSE;
}

void CheckChange(HWND hwnd, HTREEITEM hItem)
{
	HWND hLstView = GetDlgItem(hwnd, IDC_PROTOLIST);
	bool isChecked = !TreeView_GetCheckState(hLstView, hItem);

	TreeView_SelectItem(hLstView, hItem);
		
	int proto = nProtocol;
	if (GlobalNudge.useByProtocol)
	{
		proto = GetSelProto(hwnd, hItem);
		ActualNudge = NULL;
		for(NudgeElementList *n = NudgeList;n != NULL; n = n->next)
		{
			if(n->item.iProtoNumber == proto)
				ActualNudge = &n->item;
		}
	}
	else
		ActualNudge = &DefaultNudge;

	if (ActualNudge)// fix NULL pointer then no nudge support protocols
		ActualNudge->enabled = isChecked;

	UpdateControls(hwnd);
}

void UpdateControls(HWND hwnd)
{
	int proto = nProtocol;
	if (GlobalNudge.useByProtocol)
	{
		proto = GetSelProto(hwnd,NULL);
		ActualNudge = NULL;
		for(NudgeElementList *n = NudgeList;n != NULL; n = n->next)
		{
			if(n->item.iProtoNumber == proto)
				ActualNudge = &n->item;
		}
	}
	else
		ActualNudge = &DefaultNudge;

	SetDlgItemInt(hwnd, IDC_SENDTIME, GlobalNudge.sendTimeSec,FALSE);
	SetDlgItemInt(hwnd, IDC_RECVTIME, GlobalNudge.recvTimeSec,FALSE);
	SetDlgItemInt(hwnd, IDC_RESENDDELAY, GlobalNudge.resendDelaySec,FALSE);
	CheckDlgButton(hwnd, IDC_USEBYPROTOCOL, (WPARAM) GlobalNudge.useByProtocol);

	if (ActualNudge)// fix NULL pointer then no nudge support protocols
	{
		CheckDlgButton(hwnd, IDC_CHECKPOP, (WPARAM) ActualNudge->showPopup);
		CheckDlgButton(hwnd, IDC_CHECKCLIST, (WPARAM) ActualNudge->shakeClist);
		CheckDlgButton(hwnd, IDC_CHECKCHAT, (WPARAM) ActualNudge->shakeChat);
		CheckDlgButton(hwnd, IDC_CHECKSTATUS, (WPARAM) ActualNudge->showStatus);
		CheckDlgButton(hwnd, IDC_AUTORESEND, (WPARAM) ActualNudge->autoResend);
		CheckDlgButton(hwnd, IDC_OPENMESSAGE, (WPARAM) ActualNudge->openMessageWindow);
		CheckDlgButton(hwnd, IDC_OPENCONTACTLIST, (WPARAM) ActualNudge->openContactList);
		CheckDlgButton(hwnd, IDC_IGNORE, (WPARAM) ActualNudge->useIgnoreSettings);
		EnableWindow(GetDlgItem(hwnd,IDC_RESENDDELAY),ActualNudge->autoResend);	
		CheckDlgButton(hwnd,IDC_CHECKST0,ActualNudge->statusFlags & NUDGE_ACC_ST0 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST1,ActualNudge->statusFlags & NUDGE_ACC_ST1 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST2,ActualNudge->statusFlags & NUDGE_ACC_ST2 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST3,ActualNudge->statusFlags & NUDGE_ACC_ST3 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST4,ActualNudge->statusFlags & NUDGE_ACC_ST4 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST5,ActualNudge->statusFlags & NUDGE_ACC_ST5 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST6,ActualNudge->statusFlags & NUDGE_ACC_ST6 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST7,ActualNudge->statusFlags & NUDGE_ACC_ST7 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST8,ActualNudge->statusFlags & NUDGE_ACC_ST8 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwnd,IDC_CHECKST9,ActualNudge->statusFlags & NUDGE_ACC_ST9 ? BST_CHECKED : BST_UNCHECKED);
		SetDlgItemText(hwnd,IDC_SENDTEXT,ActualNudge->senText);
		SetDlgItemText(hwnd,IDC_RECVTEXT,ActualNudge->recText);
	}
	else
	{
		EnableWindow(GetDlgItem(hwnd,IDC_PROTOLIST),FALSE);
	}
}

int GetSelProto(HWND hwnd, HTREEITEM hItem)
{
	HWND hLstView = GetDlgItem(hwnd, IDC_PROTOLIST);
	TVITEM tvi = {0};

	tvi.mask = TVIF_IMAGE;
	tvi.hItem = hItem == NULL ? TreeView_GetSelection(hLstView) : hItem;

	TreeView_GetItem(hLstView, &tvi);

	return tvi.iImage;
}