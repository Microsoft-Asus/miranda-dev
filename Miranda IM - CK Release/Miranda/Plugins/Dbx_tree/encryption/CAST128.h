/*
dbx_tree: tree database driver for Miranda IM

Copyright 2007-2012 Michael "Protogenes" Kunz

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

===============================================================================
*/

#pragma once

#include "Cipher.h"

class CAST128 : public CCipher
{
private:
	uint32_t Km[16], Kr[16];

	void EncryptBlock(uint8_t *Block);
	void DecryptBlock(uint8_t *Block);
	void CreateSubKeys(uint8_t* Key);

	static const wchar_t* cName;
	static const wchar_t* cDescription;
	static const uint32_t cBlockSizeBytes = 8;
	static const bool     cIsStreamCipher = false;

public:
	const wchar_t * __cdecl Name();
	const wchar_t * __cdecl Description();
	const uint32_t  __cdecl BlockSizeBytes();
	const bool      __cdecl IsStreamCipher();

	static const TCipherInfo cCipherInfo;

	CAST128();
	~CAST128();
	static CCipher::TCipherInterface* __cdecl Create();
	
	void __cdecl SetKey(void* Key, uint32_t KeyLength);
	void __cdecl Encrypt(void* Data, uint32_t Size, uint32_t Nonce, uint32_t StartByte);
	void __cdecl Decrypt(void* Data, uint32_t Size, uint32_t Nonce, uint32_t StartByte);

};

const wchar_t* CAST128::cName          = L"Cast128";
const wchar_t* CAST128::cDescription   = L"Blockcipher - 64bit block, fast and secure, Carlisle Adams and Stafford Tavares 1996";
const TCipherInfo CAST128::cCipherInfo = {sizeof(TCipherInfo), 'Cast', cName, cDescription, &CAST128::Create};
