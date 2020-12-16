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
	SetSunPickUp(100); // ʰȡһ�����⣬�ܵ�����������100
	SetGamePause(FALSE); // �����������ʱ��Ϸ������ͣ
	SetMusicPause(FALSE); // �����������ʱ���ֲ�����ͣ
	SetNoCooldown(); // ����ȴ
}