#include "MemoryUtil.hpp"
#include "Address.hpp"

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

void patch() {
	SetSunPickUp(100); // 拾取一个阳光，总的阳光数增加100
	SetGamePause(FALSE); // 鼠标点击窗口外时游戏不会暂停
	SetMusicPause(FALSE); // 鼠标点击窗口外时音乐不会暂停
	SetNoCooldown(); // 无冷却
}