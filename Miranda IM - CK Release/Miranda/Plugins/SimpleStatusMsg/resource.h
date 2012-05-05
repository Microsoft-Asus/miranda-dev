/*
Simple Status Message plugin for 
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright (C) 2006-2011 Bartosz 'Dezeath' Bia�ek, 
			Copyright (C) 2005 Harven

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

#define IDD_COPY                        101
#define IDD_AWAYMSGBOX                  102
#define IDD_OPT_GENERAL                 103
#define IDD_READAWAYMSG                 104
#define IDI_CROSS                       105
#define IDI_HISTORY                     106
#define IDI_MESSAGE                     107
#define IDI_PLUS                        108
#define IDI_CHIST                       109
#define IDI_COPY                        110
#define IDI_CSMSG                       111
#define IDR_EDITMENU                    112
#define IDD_OPT_ADVANCED                113
#define IDD_OPT_STATUS                  114
#define IDI_GOTOURL                     115
#define IDD_OPT_VARIABLES               116
#define IDC_BOPTDEF                     1000
#define IDC_BOPTHIST                    1001
#define IDC_OK                          1002
#define IDC_EDIT1                       1003
#define IDC_CANCEL                      1004
#define IDC_ROPTMSG1                    1005
#define IDC_ROPTMSG2                    1006
#define IDC_ROPTMSG3                    1007
#define IDC_ROPTMSG4                    1008
#define IDC_ROPTMSG5                    1009
#define IDC_SPECSET                     1010
#define IDC_MSG                         1011
#define IDC_RETRIEVING                  1012
#define IDC_CLEAVEWINAMP                1013
#define IDC_COPY                        1014
#define IDC_CSTATUSLIST                 1015
#define IDC_CICONS2                     1016
#define IDC_CICONS1                     1017
#define IDC_CPROFILES                   1018
#define IDC_EMAXHIST                    1019
#define IDC_ETIMEOUT                    1020
#define IDC_CSHOWGURL                   1021
#define IDC_SMAXHIST                    1022
#define IDC_CCLOSEWND                   1023
#define IDC_STIMEOUT                    1024
#define IDC_CBOPTSTATUS                 1025
#define IDC_COPTMSG1                    1026
#define IDC_OPTEDIT1                    1027
#define IDC_CBOPTPROTO                  1028
#define IDC_ROPTPROTO1                  1029
#define IDC_ROPTPROTO2                  1030
#define IDC_ROPTPROTO3                  1031
#define IDC_CREMOVECR                   1032
#define IDC_CSHOWCOPY                   1033
#define IDC_EMAXLENGTH                  1034
#define IDC_SMAXLENGTH                  1035
#define IDC_COPTMSG2                    1036
#define IDC_VARSHELP                    1037
#define IDC_CBOPTBUTTONS                1038
#define IDC_CSHOWSMSG                   1039
#define IDC_CRPOSWND                    1040
#define IDC_ESECUPDTMSG                 1041
#define IDC_CUPDATEMSG                  1042
#define IDC_SSECUPDTMSG                 1043
#define IDC_BOPTPROTO                   1044
#define IDC_BOPTSTATUS                  1045
#define IDC_LISTPROTO                   1046
#define IDC_LISTSTATUS                  1047
#define IDC_ESETSTATUS                  1048
#define IDC_SSETSTATUS                  1049
#define IDC_NOTE1                       1050
#define IDC_POPUPDLG                    1051
#define IDC_ROPTPROTO4                  1052
#define IDC_BADD                        1053
#define IDC_BDEL                        1054
#define IDC_BCLEAR                      1055
#define IDC_CNOIDLE                     1056
#define IDC_CNOICQREQ                   1057
#define IDC_CVARIABLES                  1058
#define IDC_CDATEPARSING                1059
#define IDC_MAXLENGTH                   1060
#define IDM_VDATE                       40002
#define IDM_VWINAMPSONG                 40003
#define IDM_VRANDXY                     40004
#define IDM_VTIME                       40006
#define IDM_CUT                         40007
#define IDM_COPY                        40008
#define IDM_PASTE                       40009
#define IDM_DELETE                      40010
#define IDM_SELECTALL                   40011
#define ID__FORTUNE                     40012
#define ID__FORTUNEAWAYMSG_PROTOFORTUNEMSG 40013
#define ID__FORTUNEAWAYMSG_STATUSFORTUNEMSG 40014
#define ID__VARIABLES_LSSTATUSCONTACT   40015
#define ID__VARIABLES_LSDATECONTACTFORMAT 40016
#define ID__VARIABLES_CINFOCONTACTPROPERTY 40017
#define ID__VARIABLES_MSTATUSPROTOCOL   40018
#define ID__VARIABLES_LSTIMECONTACTFORMAT 40019
#define ID__VARIABLES_DBSETTINGCONTACTMODULESETTING 40020
#define ID__VARIABLES_TXTFILEFILELINE   40021
#define ID__VARIABLES_IFCONDITIONTRUEFALSE 40022
#define ID__VARIABLES_STRCMPSTRING1STRING2 40023
#define ID__VARIABLES_STRICMPSTRING1STRING2 40024
#define ID__VARIABLES_CDATEFORMAT       40025
#define ID__VARIABLES_CTIMEFORMAT       40026
#define ID__VARIABLES_REPLACESUBSTRING1STRING2 40027
#define ID__VARIABLES_LOWERSTRING       40028
#define ID__VARIABLES_UPPERSTRING       40029
#define ID__VARIABLES_CONTACTSTRINGPROPERTY 40030
#define ID__VARIABLES_SCROLLSTRINGNUMCHARSNUMCHARS 40031
#define ID__VARIABLES_MOREVARIABLES     40032
#define ID__VARIABLES                   40033
#define ID__FORTUNEAWAYMSG              40034
#define IDM_VRANDMSG                    40035
#define IDM_VRANDDEFMSG                 40036

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        117
#define _APS_NEXT_COMMAND_VALUE         40037
#define _APS_NEXT_CONTROL_VALUE         1061
#define _APS_NEXT_SYMED_VALUE           100
#endif
#endif
