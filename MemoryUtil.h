#ifndef _MEMORY_UTIL_
#define _MEMORY_UTIL_

#include <windows.h>

void SetMemWrtieable(DWORD address, SIZE_T size);

DWORD ReadDword(DWORD address);

void WriteDword(DWORD address, DWORD value);

BYTE ReadByte(DWORD address);

void WriteByte(DWORD address, BYTE value);

void WriteBytes(DWORD address, SIZE_T n, DWORD value, ...);

void WriteString(DWORD address, LPCSTR str);

void WriteCall(DWORD address, DWORD func);

void WriteNop(DWORD address, SIZE_T size);

void WriteJmpRel32(DWORD address, DWORD dest);
#endif