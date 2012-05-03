/*
Jabber Protocol plugin for
Miranda IM: the free IM client for Microsoft* Windows*

Authors 
			Copyright (C) 2002-2004		Santithorn Bunchua
			Copyright (C) 2007			Maxim Mluhov, Victor Pavlychko, Artem Shpynov, Michael Stepura
			Copyright (C) 2008-09		Dmitriy Chervov
			Copyright (C) 2005-2012		George Hazan, Borkra

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

#define IDD_OPT_JABBER                  101
#define IDI_JABBER                      102
#define IDD_INFO_JABBER                 103
#define IDD_OPT_REGISTER                105
#define IDD_AGENTS                      106
#define IDD_FORM                        107
#define IDI_ADDROSTER                   108
#define IDI_USER2ROOM                   109
#define IDI_REFRESH                     110
#define IDD_PASSWORD                    111
#define IDI_ADDCONTACT                  122
#define IDI_DELETE                      123
#define IDI_EDIT                        124
#define IDD_DATAFORM_TEST               125
#define IDD_VCARD_HOME                  126
#define IDD_VCARD_PERSONAL              127
#define IDD_VCARD_WORK                  128
#define IDD_VCARD_CONTACT               129
#define IDD_VCARD_ADDEMAIL              130
#define IDD_VCARD_ADDPHONE              131
#define IDI_OPEN                        131
#define IDD_VCARD_PHOTO                 132
#define IDD_VCARD_NOTE                  133
#define IDD_CHANGEPASSWORD              136
#define IDD_SEARCHUSER                  138
#define IDD_OPT_JABBER2                 140
#define IDI_REQUEST                     141
#define IDD_GROUPCHAT                   141
#define IDI_GRANT                       142
#define IDI_KEYS                        144
#define IDI_GROUP                       147
#define IDD_GROUPCHAT_JOIN              148
#define IDI_AGENTS                      154
#define IDI_VCARD                       155
#define IDI_SAVE                        166
#define IDD_GROUPCHAT_INPUT             167
#define IDD_JIDLIST                     171
#define IDD_AGENT_MANUAL_REGISTER       182
#define IDD_GROUPCHAT_INVITE            183
#define IDD_GROUPCHAT_INVITE_ACCEPT     184
#define IDD_OPT_JABBER3                 185
#define IDI_LOGIN                       186
#define IDI_AUTHREVOKE                  187
#define IDI_COMMAND                     188
#define IDI_DISCO_OK                    190
#define IDI_DISCO_FAIL                  191
#define IDI_VIEW_LIST                   192
#define IDI_VIEW_TREE                   193
#define IDI_FILTER_APPLY                194
#define IDI_BROWSE                      195
#define IDI_NAV_HOME                    196
#define IDI_NAV_REFRESH                 197
#define IDI_FILTER_RESET                198
#define IDI_DISCO_PROGRESS              199
#define IDI_NODE_RSS                    200
#define IDI_NODE_SERVER                 201
#define IDI_NODE_STORE                  202
#define IDI_NODE_WEATHER                203
#define IDD_CONSOLE                     205
#define IDI_CONSOLE                     207
#define IDD_DATAFORM_PAGE               208
#define IDI_PL_MSG_ALLOW                209
#define IDI_PL_MSG_DENY                 210
#define IDI_PL_PRIN_ALLOW               211
#define IDI_PL_PRIN_DENY                212
#define IDI_PL_PROUT_ALLOW              213
#define IDI_PL_PROUT_DENY               214
#define IDI_PL_QUERY_ALLOW              215
#define IDD_SETMOODMSG                  216
#define IDI_PL_QUERY_DENY               216
#define IDI_PL_LIST_ACTIVE              217
#define IDI_PL_LIST_ANY                 218
#define IDI_PL_LIST_DEFAULT             219
#define IDI_ARROW_DOWN                  220
#define IDI_ARROW_UP                    221
#define IDI_TRANSPORT                   222
#define IDI_TRANSPORTL                  223
#define IDD_GROUPCHAT_INFO              224
#define IDD_OPT_JABBER4                 226
#define IDD_ACCMGRUI                    227
#define IDD_HTTP_AUTH                   228
#define IDI_HTTP_AUTH                   229
#define IDD_PEP_SIMPLE                  230
#define IDD_NOTEBOOK                    231
#define IDD_NOTE_EDIT                   232
#define IDI_NOTES                       233
#define IDI_SEND_NOTE                   234
#define IDC_STATUSBAR                   999
#define IDC_EDIT_USERNAME               1000
#define IDC_SAVE                        1000
#define IDC_EDIT_PASSWORD               1001
#define IDC_BUTTON_REGISTER             1002
#define IDC_EDIT_LOGIN_SERVER           1003
#define IDC_PORT                        1004
#define IDC_BUTTON_CHANGE_PASSWORD      1005
#define IDC_LINK_PUBLIC_SERVER          1009
#define IDC_NAME                        1009
#define IDC_PROGRESS_REG                1011
#define IDC_AGENT_TRANSPORT             1015
#define IDC_AGENT_REGISTER              1016
#define IDC_AGENT_LOGON                 1017
#define IDC_AGENT_UNREGISTER            1018
#define IDC_AGENT_SERVER                1019
#define IDC_AGENT_LOGOFF                1020
#define IDC_AGENT_LIST                  1021
#define IDC_AGENT_SEARCH                1022
#define IDC_SUBMIT                      1023
#define IDC_NEXT                        1025
#define IDC_PREV                        1026
#define IDC_COMPLETE                    1027
#define IDC_AGENT_BROWSE                1029
#define IDC_INSTRUCTION                 1030
#define IDC_FRAME                       1037
#define IDC_FRAME_TEXT                  1038
#define IDC_SIMPLE                      1041
#define IDC_KEEPALIVE                   1042
#define IDC_HOST                        1043
#define IDC_HOSTPORT                    1044
#define IDC_USE_SSL                     1045
#define IDC_MANUAL                      1046
#define IDC_RESOURCE_T                  1047
#define IDC_SAVEPASSWORD                1048
#define IDC_MSGLANG                     1049
#define IDC_PASSWORD                    1050
#define IDC_JID                         1051
#define IDC_NEWPASSWD2                  1052
#define IDC_ROSTER_SYNC                 1052
#define IDC_OLDPASSWD                   1053
#define IDC_ADDRESS1                    1056
#define IDC_ADDRESS2                    1057
#define IDC_CITY                        1058
#define IDC_STATE                       1059
#define IDC_COUNTRY                     1060
#define IDC_FULLNAME                    1061
#define IDC_ZIP                         1061
#define IDC_NICKNAME                    1062
#define IDC_COMPANY                     1062
#define IDC_FIRSTNAME                   1063
#define IDC_DEPARTMENT                  1063
#define IDC_LASTNAME                    1064
#define IDC_BIRTH                       1065
#define IDC_OCCUPATION                  1066
#define IDC_HOMEPAGE                    1067
#define IDC_MIDDLE                      1072
#define IDC_EMAIL                       1073
#define IDC_HOME                        1074
#define IDC_INTERNET                    1075
#define IDC_X400                        1076
#define IDC_WORK                        1077
#define IDC_PHONE                       1078
#define IDC_CELL                        1079
#define IDC_VIDEO                       1080
#define IDC_BBS                         1081
#define IDC_MODEM                       1082
#define IDC_PAGER                       1083
#define IDC_MSG                         1084
#define IDC_ISDN                        1085
#define IDC_PCS                         1086
#define IDC_VOICE                       1087
#define IDC_FAX                         1088
#define IDC_TITLE                       1089
#define IDC_DESC                        1090
#define IDC_DELETE                      1092
#define IDC_LOAD                        1093
#define IDC_CANVAS                      1094
#define IDC_GENDER                      1096
#define IDC_JUD                         1097
#define IDC_JUD_LABEL                   1098
#define IDC_MSGLANG_LABEL               1099
#define IDC_PRIORITY_SPIN               1104
#define IDC_PRIORITY                    1105
#define IDC_PRIORITY_LABEL              1106
#define IDC_NEWPASSWD                   1107
#define IDC_COMBO_ACCTYPE               1108
#define IDD_MODERNOPT                   1110
#define IDC_PROXY_ADDR                  1112
#define IDC_DIRECT_ADDR                 1114
#define IDC_DIRECT_MANUAL               1121
#define IDC_REG_STATUS                  1122
#define IDC_JOIN                        1123
#define IDC_DIRECT                      1123
#define IDC_ROOM                        1124
#define IDC_PROXY_MANUAL                1124
#define IDC_SERVER                      1125
#define IDC_BROWSE                      1126
#define IDC_VSCROLL                     1128
#define IDC_NICK                        1129
#define IDC_EDIT                        1131
#define IDC_LIST                        1133
#define IDC_TABS                        1141
#define IDC_TXT_MULTILINE               1141
#define IDC_TXT_PASSWORD                1142
#define IDC_MANUAL_REGISTER             1167
#define IDC_REASON                      1171
#define IDC_CLIST                       1172
#define IDC_NEWJID                      1173
#define IDC_ADDJID                      1174
#define IDC_INVITE                      1175
#define IDC_BTN_ADVANCED                1175
#define IDC_ACCEPT                      1176
#define IDC_BTN_SIMPLE                  1176
#define IDC_FROM                        1177
#define IDC_USE_TLS                     1180
#define IDC_UNREGISTER                  1183
#define IDC_GO                          1196
#define IDC_HOSTNAME_AS_RESOURCE        1214
#define IDC_COMMANDS1                   1216
#define IDC_COMMANDS2                   1217
#define IDC_COMBO_RESOURCE              1218
#define IDC_PL_RULES_LIST               1219
#define IDC_WHITERECT                   1220
#define IDC_ADD_RULE                    1221
#define IDC_EDIT_RULE                   1222
#define IDC_REMOVE_RULE                 1223
#define IDC_ADD_LIST                    1225
#define IDC_REMOVE_LIST                 1226
#define IDC_COMBO_TYPE                  1230
#define IDC_EDIT_VALUE                  1231
#define IDC_COMBO_ACTION                1232
#define IDC_CHECK_MESSAGES              1233
#define IDC_CHECK_QUERIES               1234
#define IDC_CHECK_PRESENCE_OUT          1235
#define IDC_CHECK_PRESENCE_IN           1236
#define IDC_COMBO_VALUE                 1237
#define IDC_EDIT_NAME                   1238
#define IDC_TREE_DISCO                  1240
#define IDC_FRAME1                      1241
#define IDC_FRAME2                      1242
#define IDC_COMBO_JID                   1243
#define IDC_TXT_JID                     1243
#define IDC_COMBO_NODE                  1244
#define IDC_BUTTON_BROWSE               1245
#define IDC_DOWNLOAD                    1245
#define IDC_ACTIVATE                    1245
#define IDC_BTN_NAVHOME                 1246
#define IDC_UPLOAD                      1246
#define IDC_TXT_FILTERTEXT              1247
#define IDC_IMPORT                      1247
#define IDC_BTN_FILTERRESET             1248
#define IDC_EXPORT                      1248
#define IDC_TXT_FILTER                  1249
#define IDC_TXT_NODELABEL               1250
#define IDC_BTN_FAVORITE                1251
#define IDC_BTN_REFRESH                 1253
#define IDC_BTN_VIEWTREE                1254
#define IDC_BTN_VIEWLIST                1255
#define IDC_BTN_FILTERAPPLY             1258
#define IDC_ROSTER                      1261
#define IDC_MSG_MOOD                    1262
#define IDC_OPTTREE                     1263
#define IDC_LB_LISTS                    1264
#define IDC_LST_NOTES                   1264
#define IDC_TITLE1                      1265
#define IDC_CONSOLE                     1266
#define IDC_CONSOLEIN                   1267
#define IDC_RESET                       1268
#define IDC_BOOKMARKS                   1270
#define IDC_BTN_MSG                     1270
#define IDC_BTN_ROLE                    1270
#define IDC_DATAFORM                    1270
#define IDC_BTN_PRESENCE                1271
#define IDC_BTN_AFFILIATION             1271
#define IDC_SET_DEFAULT                 1272
#define IDC_BTN_IQ                      1272
#define IDC_TXT_RULES                   1273
#define IDC_TXT_LISTS                   1274
#define IDC_TV_INFO                     1276
#define IDC_TXT_OTHERJID                1277
#define IDC_TXT_MESSAGE                 1278
#define IDC_TXT_QUERY                   1279
#define IDC_TXT_INPRESENCE              1280
#define IDC_TXT_OUTPRESENCE             1281
#define IDC_ICO_OUTPRESENCE             1282
#define IDC_ICO_INPRESENCE              1283
#define IDC_ICO_QUERY                   1284
#define IDC_ICO_MESSAGE                 1285
#define IDC_ICO_PRESENCEIN              1286
#define IDC_ICO_PRESENCEOUT             1287
#define IDC_RECENT1                     1288
#define IDC_RECENT2                     1289
#define IDC_RECENT3                     1290
#define IDC_RECENT4                     1291
#define IDC_RECENT5                     1292
#define IDC_TXT_RECENT                  1293
#define IDC_FILTER                      1294
#define IDC_TXT_NICK                    1294
#define IDC_TXT_QUIT                    1294
#define IDC_EDIT_HTTP_AUTH_INFO         1294
#define IDC_TXT_URL                     1294
#define IDC_TXT_DESCRIPTION             1294
#define IDC_TXT_TITLE                   1294
#define IDC_BTN_FILTER                  1295
#define IDC_TXT_ID                      1295
#define IDC_CB_FILTER                   1296
#define IDC_TXT_ROLE                    1296
#define IDC_TXT_COMBO                   1296
#define IDC_CB_TYPE                     1296
#define IDC_TXT_METHOD                  1296
#define IDC_CB_MODES                    1296
#define IDC_BTN_FILTER_REFRESH          1297
#define IDC_TXT_STATUS                  1298
#define IDC_TXT_FROM                    1298
#define IDC_TXT_AFFILIATION             1299
#define IDC_ICO_STATUS                  1300
#define IDC_TXT_RICHEDIT                1302
#define IDC_TXT_SLAP                    1304
#define IDC_TXT_TAGS                    1304
#define IDC_EMAILS                      1306
#define IDC_TV_FILTER                   1307
#define IDC_PHONES                      1308
#define IDC_TXT_TEXT                    1308
#define IDC_ST_TAGS                     1309
#define IDC_INSTRUCTIONS                1315
#define IDC_COMBO_VALUES                1319
#define IDC_HEADERBAR                   1320
#define IDC_USEDOMAINLOGIN              1323
#define IDC_TXT_ALTNICK                 1323
#define IDI_BOOKMARKS                   3000
#define IDD_BOOKMARKS                   3001
#define IDC_BM_LIST                     3002
#define IDC_ADD                         3004
#define IDC_REMOVE                      3005
#define IDD_BOOKMARK_ADD                3006
#define IDC_UP_RULE                     3006
#define IDC_ROOM_JID                    3007
#define IDD_PRIVACY_LISTS               3007
#define IDC_DOWN_RULE                   3007
#define IDC_APPLY                       3008
#define IDD_PRIVACY_RULE                3008
#define IDC_ROOM_RADIO                  3009
#define IDD_PRIVACY_ADD_LIST            3009
#define IDD_SERVICE_DISCOVERY           3010
#define IDC_URL_RADIO                   3011
#define IDD_GROUPCHAT_INFO_TABS         3011
#define IDC_AGENT_RADIO                 3012
#define IDD_GROUPCHAT_ADMLIST           3012
#define IDC_BOOKMARK_TYPE               3013
#define IDC_CHECK_BM_AUTOJOIN           3014
#define IDI_PRIVACY_LISTS               3016
#define IDI_SERVICE_DISCOVERY           3017
#define IDD_CAPTCHAFORM                 3018
#define IDC_VALUE                       3019

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC                     1
#define _APS_NEXT_RESOURCE_VALUE        235
#define _APS_NEXT_COMMAND_VALUE         40017
#define _APS_NEXT_CONTROL_VALUE         1324
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
