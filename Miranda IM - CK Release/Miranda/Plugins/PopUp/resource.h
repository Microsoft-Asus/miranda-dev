/*
Popup Plus plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Authors
			Copyright (C)	2002 Luca Santarelli
							2004-2007 Victor Pavlychko
							2010-2012 Merlin_de, MPK

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

#define IDD_OPT_POPUP                   101
#define IDD_OPT_POPUP_ADVANCED          102
#define IDD_OPT_SKIN2                   103
#define IDD_OPT_ACTIONS                 104
#define IDD_OPT_NOTIFICATIONS           105
#define IDD_OPT_CONTACTS                106
#define IDD_OPT_POPUP_GENERAL           107
#define IDD_HISTORY                     108
#define IDD_POSITION                    109
#define IDB_NOAVATAR                    110
#define IDR_WHATSNEW                    111
#define IDI_POPUP                       118
#define IDI_NOPOPUP                     120
#define IDI_HISTORY                     184
#define IDI_RELOAD                      185
#define IDI_MB_STOP                     189
#define IDI_MB_INFO                     191
#define IDI_MB_WARN                     194
#define IDI_RESIZE                      196
#define IDI_OPT_CHECK_OFF               198
#define IDI_OPT_CHECK_ON                199
#define IDI_OPT_RADIO_OFF               200
#define IDI_OPT_RADIO_ON                201
#define IDI_ACT_INFO                    203
#define IDI_ACT_MENU                    204
#define IDI_ACT_MESSAGE                 205
#define IDI_ACT_OK                      206
#define IDI_ACT_ADD                     207
#define IDI_ACT_CLOSE                   208
#define IDI_ACT_PINNED                  209
#define IDI_ACT_PIN                     210
#define IDI_ACT_COPY                    211
#define IDI_OPT_GROUP                   213
#define IDI_OPT_FULLSCREEN              215
#define IDI_OPT_BLOCK                   216
#define IDI_OPT_FAVORITE                217
#define IDI_OPT_AUTO                    218
#define IDI_ACT_REPLY                   219
#define IDI_PU_FULLSCREEN               221
#define IDI_PU_FAVOURITE                222
#define IDC_USEANIMATIONS               1005
#define IDC_EFFECT_TXT                  1006
#define IDC_EFFECT                      1007
#define IDC_FADEIN_TXT1                 1008
#define IDC_FADEIN                      1009
#define IDC_FADEIN_SPIN                 1010
#define IDC_FADEIN_TXT2                 1011
#define IDC_FADEOUT_TXT1                1012
#define IDC_FADEOUT                     1013
#define IDC_FADEOUT_SPIN                1014
#define IDC_FADEOUT_TXT2                1015
#define IDC_PREVIEW                     1033
#define IDC_DEBUG                       1034
#define IDC_GRP_MULTIMONITOR            1035
#define IDC_MULTIMONITOR_DESC           1036
#define IDC_MIRANDAWND                  1037
#define IDC_ACTIVEWND                   1038
#define IDC_AVT_BORDER                  1050
#define IDC_AVT_PNGBORDER               1051
#define IDC_AVT_RADIUS                  1053
#define IDC_AVT_RADIUS_SPIN             1054
#define IDC_AVT_SIZE_SLIDE              1057
#define IDC_AVT_SIZE                    1058
#define IDC_AVT_REQUEST                 1059
#define IDC_TRANS_9X                    1062
#define IDC_TRANS                       1063
#define IDC_TRANS_TXT1                  1064
#define IDC_TRANS_SLIDER                1065
#define IDC_TRANS_PERCENT               1066
#define IDC_TRANS_OPAQUEONHOVER         1067
#define IDC_CHECKWINDOW                 1095
#define IDC_LACTION                     1096
#define IDC_RACTION                     1097
#define IDC_SOFFLINE                    1099
#define IDC_SONLINE                     1100
#define IDC_SAWAY                       1101
#define IDC_SNA                         1102
#define IDC_SOCCUPIED                   1103
#define IDC_SDND                        1104
#define IDC_SFREE4CHAT                  1105
#define IDC_SINVISIBLE                  1106
#define IDC_SPHONE                      1107
#define IDC_SLUNCH                      1108
#define IDC_TIMEOUT                     1110
#define IDC_SOFFLINE2                   1111
#define IDC_SONLINE2                    1112
#define IDC_SAWAY2                      1113
#define IDC_SNA2                        1114
#define IDC_SOCCUPIED2                  1115
#define IDC_SDND2                       1116
#define IDC_TREE1                       1117
#define IDC_SKINLIST                    1118
#define IDC_SINVISIBLE2                 1119
#define IDC_SPHONE2                     1120
#define IDC_SLUNCH2                     1121
#define IDC_TXT_TIMEOUT_SEC             1122
#define IDC_PREVIEWBOX                  1123
#define IDC_TXT_TIMEOUT_INFINITE        1124
#define IDC_SFREE4CHAT2                 1125
#define IDC_TXT_TIMEOUT_DEFAULT         1126
#define IDC_POPUP_LIST                  1134
#define IDC_SHOWHISTORY                 1135
#define IDC_ENABLE_HISTORY              1137
#define IDC_HPPLOG                      1138
#define IDC_BTN_RELOAD                  1144
#define IDC_MAXPOPUPS                   1145
#define IDC_HISTORY_STATIC1             1147
#define IDC_HISTORY_STATIC2             1148
#define IDC_HISTORYSIZE                 1149
#define IDC_TITLE                       1150
#define IDC_TXT_TOP                     1163
#define IDC_TIMEOUT_SPIN                1164
#define IDC_TXT_LEFT                    1165
#define IDC_TXT_RIGHT                   1166
#define IDC_TXT_BOTTOM                  1167
#define IDC_TXT_SPACING                 1168
#define IDC_LIST                        1169
#define IDC_ACTIONS                     1170
#define IDC_CHK_ENABLEACTIONS           1175
#define IDC_CHK_IMCONTACTSONLY          1176
#define IDC_CHK_LARGEICONS              1177
#define IDC_CHK_CONTACTSONLY            1178
#define IDC_CHK_DONTCLOSE               1179
#define IDC_RD_TEXT                     1180
#define IDC_RD_RIGHTICONS               1181
#define IDC_RD_LEFTICONS                1182
#define IDC_ICO_INFO                    1183
#define IDC_GRP_CUSTOMACTIONS           1185
#define IDC_GRP_SIZEPOSITION            1186
#define IDC_GRP_ACTIONS                 1187
#define IDC_TXT_CUSTOMACTIONS           1189
#define IDC_TXT_POSITION                1190
#define IDC_ICO_RESTART                 1191
#define IDC_MORE                        1193
#define IDC_TXT_TITLE1                  1194
#define IDC_TXT_POSITION2               1195
#define IDC_TXT_TITLE3                  1196
#define IDC_TXT_TITLE4                  1197
#define IDC_ENABLE                      1198
#define IDC_TXT_TIMEOUT                 1199
#define IDC_TXT_LACTION                 1200
#define IDC_TXT_RACTION                 1201
#define IDC_TXT_COLORS                  1202
#define IDC_ICO_FAVORITE                1203
#define IDC_ICO_FULLSCREEN              1204
#define IDC_ICO_BLOCK                   1205
#define IDC_ICO_AUTO                    1206
#define IDC_GRP_SIZEPOSITION2           1207
#define IDC_ICO_OK                      1208
#define IDC_CB_RIGHT                    1213
#define IDC_CB_MIDDLE                   1214
#define IDC_CB_LEFT                     1215
#define IDC_TXT_MIDDLE                  1216
#define IDC_SKIN_LIST_OPT               1217
#define IDC_INFINITEDELAY               1218
#define IDC_SECONDS_STATIC1             1219
#define IDC_SECONDS                     1220
#define IDC_SECONDS_SPIN                1221
#define IDC_SECONDS_STATIC2             1222
#define IDC_LEAVEHOVERED                1223
#define IDC_DYNAMICRESIZE               1225
#define IDC_USEMINIMUMWIDTH             1226
#define IDC_MINIMUMWIDTH                1227
#define IDC_MINIMUMWIDTH_SPIN           1228
#define IDC_USEMAXIMUMWIDTH             1229
#define IDC_MAXIMUMWIDTH                1230
#define IDC_MAXIMUMWIDTH_SPIN           1231
#define IDC_WHERE                       1233
#define IDC_CUSTOMPOS                   1234
#define IDC_LAYOUT                      1236
#define IDC_REORDERPOPUPS               1238
#define IDC_POPUPENABLED                1240
#define IDC_DISABLEINFS                 1241
#define IDC_STATUSES                    1242
#define IDC_GETSKINS                    1243
#define IDC_CHK_OFFLINE                 40071
#define IDC_CHK_ONLINE                  40072
#define IDC_CHK_NA                      40075
#define IDC_CHK_OCCUPIED                40076
#define IDC_CHK_ONTHEPHONE              40079
#define IDC_CHK_OUTTOLUNCH              40080

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        224
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1244
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
