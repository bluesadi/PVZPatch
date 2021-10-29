#include "Debug.h"

void DebugBox(DWORD dwNum) {
	WCHAR content[100] = { 0 };
	wsprintf(content, L"%x", dwNum);
	MessageBox(NULL, content, L"Debug", MB_OK);
}