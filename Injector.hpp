#include "MemoryUtil.hpp"
#include "Address.hpp"
#define DLL_EXPORT extern "C" __declspec(dllexport)

void SetSunPickUp(DWORD sunPickUp) {
	WriteDword(SUN_PICK_UP_ADDRESS, sunPickUp);
}

void SetGamePause(BOOL gamePause) {
	if (gamePause == FALSE) {
		WriteByte(JMP_GAME_PAUSE_ADDRESS, 0xEB);
	}else {
		WriteByte(JMP_GAME_PAUSE_ADDRESS, 0x74);
	}
}

void SetMusicPause(BOOL musicPause) {
	if (musicPause == FALSE) {
		WriteByte(JMP_MUSIC_PAUSE_ADDRESS, 0xEB);
	}else {
		WriteByte(JMP_MUSIC_PAUSE_ADDRESS, 0x74);
	}
}

void SetNoCooldown() {
	WriteByte(SET_COOLDOWN_ADDRESS, 0x01);
}

DLL_EXPORT void CALL_BACK() {
	MessageBox(NULL, L"call back", L"call back", MB_OK);
}

void TestCallBack() {
	WriteBytes(0x0044F475, 3, 0x90, 0x90, 0x90);
	WriteCall(0x0044F475 + 3, (DWORD)CALL_BACK);
}

void Repair() {
	DWORD EP = 0x0021EBE7;
	WriteBytes(EP, 11, 0xB8, 0xFF, 0x00, 0x00, 0x00, 0xE8, 0xA0, 0xBC, 0x00, 0x00, 0xC3);
	DWORD DLLNameOffset = 0x00272A60;
	WriteString(DLLNameOffset, "DBGHELP.DLL");
}

void patch() {
	Repair(); //修复程序
	SetSunPickUp(50); // 拾取一个阳光，总的阳光数增加100
	//SetGamePause(FALSE); // 鼠标点击窗口外时游戏不会暂停
	TestCallBack();
	SetMusicPause(FALSE); // 鼠标点击窗口外时音乐不会暂停
	SetNoCooldown(); // 无冷却
}