#ifndef _INJECT_
#define _INJECT_

#include "MemoryUtil.h"
#include "Debug.h"
#include "Address.h"
#define DLL_EXPORT extern "C" __declspec(dllexport)

void SetSunPickUp(DWORD sunPickUp);

void SetGamePause(BOOL gamePause);

void SetMusicPause(BOOL musicPause);

void SetNoCooldown();

void SetUnlimitedSun();

void SetZomieTideMode();

void Inject();

#endif