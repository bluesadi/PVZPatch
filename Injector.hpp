#include "MemoryUtil.hpp"
#include "Address.hpp"

void SetSunPickUp(DWORD sunPickUp) {
	WriteDword(SUN_PICK_UP_ADDRESS, sunPickUp);
}

void patch() {
	SetSunPickUp(100); // ʰȡһ�����⣬�ܵ�����������100
}