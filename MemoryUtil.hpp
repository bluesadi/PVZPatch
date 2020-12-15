#include <windows.h>
#include <Tlhelp32.h>
#include <Psapi.h>

HANDLE getPVZProcess() {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	while (Process32Next(hSnapshot, &processInfo)) {
		if (!lstrcmp(processInfo.szExeFile, L"PlantsVsZombies.exe")) {
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, processInfo.th32ProcessID);
			return hProcess;
		}
	}
	return NULL;
}

HANDLE hPVZProcess = getPVZProcess();

DWORD ReadDword(DWORD address) {
	DWORD result, dwret;
	ReadProcessMemory(hPVZProcess, (LPVOID)address, &result, sizeof(DWORD), &dwret);
	return result;
}

void WriteDword(DWORD address, DWORD value) {
	DWORD dwret;
	WriteProcessMemory(hPVZProcess, (LPVOID)address, &value, sizeof(DWORD), &dwret);
}

BYTE ReadByte(DWORD address) {
	BYTE result;
	DWORD dwret;
	ReadProcessMemory(hPVZProcess, (LPVOID)address, &result, sizeof(BYTE), &dwret);
	return result;
}

void WriteByte(DWORD address, BYTE value) {
	DWORD dwret;
	WriteProcessMemory(hPVZProcess, (LPVOID)address, &value, sizeof(BYTE), &dwret);
}

void WriteBytes(DWORD address, INT n, DWORD value, ...) {
	DWORD dwret;
	for (int i = 0; i < n; i++) {
		WriteByte(address + i, (&value)[i]);
	}
}

void WriteCall(DWORD from, DWORD to) {
	DWORD rel32 = to - (from + 5);
	BYTE* lprel32 = (BYTE*)&rel32;
	WriteBytes(from, 5, 0xE8, lprel32[0], lprel32[1], lprel32[2], lprel32[3]);
}

void WriteJmpRel32(DWORD from, DWORD to) {
	DWORD rel32 = to - (from + 5);
	BYTE* lprel32 = (BYTE*)&rel32;
	WriteBytes(from, 5, 0xE9, lprel32[0], lprel32[1], lprel32[2], lprel32[3]);
}