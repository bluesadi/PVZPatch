#include "Injector.h"
#include "ZombieType.h"
#include <cstdlib>
#include <ctime>

void SetSunPickUp(DWORD sunPickUp) {
	WriteDword(SUN_PICK_UP_ADDRESS, sunPickUp);
}

void SetGamePause(BOOL gamePause) {
	if (gamePause == FALSE) {
		WriteByte(JMP_GAME_PAUSE_ADDRESS, 0xEB);
	}
	else {
		WriteByte(JMP_GAME_PAUSE_ADDRESS, 0x74);
	}
}

void SetMusicPause(BOOL musicPause) {
	if (musicPause == FALSE) {
		WriteByte(JMP_MUSIC_PAUSE_ADDRESS, 0xEB);
	}
	else {
		WriteByte(JMP_MUSIC_PAUSE_ADDRESS, 0x74);
	}
}

void SetNoCooldown() {
	WriteByte(SET_COOLDOWN_ADDRESS, 0x01);
}

void SetUnlimitedSun() {
	//WriteDword(SUN_ADDRESS, 9990);
	WriteNop(SUB_SUN_ADDRESS, 2);
}

DLL_EXPORT void  __stdcall CallZombie(DWORD _edi, DWORD row, DWORD zombieType) {
	DWORD func = FUNC_CALL_ZOMBIE_ADDRESS;
	for (int i = 0; i < 5; i++) {
		int t = rand() % ZOMBIE_NUM;
		__asm {
			push i			// Row
			push t			// Zombie Code
			mov eax, _edi
			call func
		}
	}
}

void SetZomieTideMode() {
	WriteByte(0x00413057, 0x57);
	WriteCall(0x00413058, (DWORD)CallZombie);
	WriteNop(0x0041305D, 1);
}

DLL_EXPORT void  __stdcall GameOver(DWORD param) {
	//DebugBox(666);
	//MessageBoxA(NULL, "Your flag is encrypted by me.\nSee your C:/ProgramData/PopCap Games/PlantsVsZombies/flag.enc", "loooooooooooooool!!!", MB_OK);
	DWORD func = FUNC_GAMEOVER_ADDRESS;
	__asm {
		push param
		call func
	}
}

void HookGameOver() {
	WriteCall(0x0043C65C, (DWORD)GameOver);
}

void Repair() {
	DWORD EP = IMAGE_BASE + 0x0021EBE7;
	WriteBytes(EP, 11, 0xB8, 0xFF, 0x00, 0x00, 0x00, 0xE8, 0xA0, 0xBC, 0x00, 0x00, 0xC3);
	DWORD DLLNameOffset = IMAGE_BASE + 0x00272A60;
	WriteString(DLLNameOffset, "DBGHELP.DLL");
}

void Inject() {
	srand(time(NULL));
	Repair(); //修复程序
#ifdef DEBUG_MODE
	SetNoCooldown(); // 无冷却
	//SetUnlimitedSun(); //无限阳光
#endif
	//SetSunPickUp(50); // 拾取一个阳光，总的阳光数增加100
	SetGamePause(FALSE); // 鼠标点击窗口外时游戏不会暂停
	SetMusicPause(FALSE); // 鼠标点击窗口外时音乐不会暂停
	SetZomieTideMode(); // 尸潮模式
	HookGameOver();
}