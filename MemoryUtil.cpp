#include "MemoryUtil.h"

void SetMemWrtieable(DWORD address, SIZE_T size) {
	DWORD old;
	VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &old);
}

DWORD ReadDword(DWORD address) {
	PDWORD p = (PDWORD)address;
	return *p;
}

void WriteDword(DWORD address, DWORD value) {
	SetMemWrtieable(address, 4);
	PDWORD p = (PDWORD)address;
	*p = value;
}

BYTE ReadByte(DWORD address) {
	PBYTE p = (PBYTE)address;
	return *p;
}

void WriteByte(DWORD address, BYTE value) {
	SetMemWrtieable(address, 1);
	PBYTE p = (PBYTE)address;
	*p = value;
}

void WriteBytes(DWORD address, SIZE_T n, DWORD value, ...) {
	for (int i = 0; i < n; i++) {
		WriteByte(address + i, (&value)[i]);
	}
}

void WriteString(DWORD address, LPCSTR str) {
	for (int i = 0; str[i]; i++) {
		WriteByte(address + i, str[i]);
	}
}

void WriteCall(DWORD address, DWORD func) {
	DWORD rel32 = func - (address + 5);
	WriteByte(address, 0xE8);
	WriteDword(address + 1, rel32);
}

void WriteNop(DWORD address, SIZE_T size) {
	for (int i = 0; i < size; i++) {
		WriteByte(address + i, 0x90);
	}
}

void WriteJmpRel32(DWORD address, DWORD dest) {
	DWORD rel32 = dest - (address + 5);
	WriteByte(address, 0xE9);
	WriteDword(address + 1, rel32);
}