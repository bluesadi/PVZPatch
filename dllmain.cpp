#include "Injector.h"
#define PATCH_VERSION L"1.0"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        WCHAR TITLE[100] = { 0 };
        wsprintf(TITLE, L"PVZ Patch (version %s)", PATCH_VERSION);
        MessageBox(NULL, L"DLL is patched to PVZ process!", TITLE, MB_OK);
        patch();
    }
    return TRUE;
}