# PVZPatch

### PVZ环境说明
测试用的PVZ版本是**1.0.0.1051汉化２版图鉴加强版**，只要不是魔改版PVZ应该都可以用。\
下载链接：http://lonelystar.org/ResDownload/1_PC_C.htm#v1.0_2

### 使用方法
首先我们需要给 PlantsVsZombies.exe 打上一些补丁，使PVZ能够加载我们的DLL文件，且不影响PVZ正常加载。\
以下是给文件打补丁的代码，用Python实现：
```py
'''
PVZPatcher.py
2020/12/15 by bluesadi
用于给 PlantsVsZombies.exe 打补丁，使其能够加载我们写的 patch.dll
'''
PVZFile = open('PlantsVsZombies.exe','rb+')

def writeBytes(offset,data):
    PVZFile.seek(offset)
    PVZFile.write(data)

'''
.text:005A38A0 81 EC 0C 01 00 00                       sub     esp, 10Ch
.text:005A38A6 A1 E8 9F 69 00                          mov     eax, ___security_cookie
.text:005A38AB 33 C4                                   xor     eax, esp
.text:005A38AD 89 84 24 08 01 00 00                    mov     [esp+10Ch+var_4], eax
.text:005A38B4 56                                      push    esi
.text:005A38B5 8B 35 A4 20 65 00                       mov     esi, ds:LoadLibraryA
.text:005A38BB 68 60 2A 67 00                          push    offset aDbghelpDll ; "DBGHELP.DLL"
.text:005A38C0 FF D6                                   call    esi ; LoadLibraryA
.text:005A38C2 85 C0                                   test    eax, eax
.text:005A38C4 A3 94 9F 6A 00                          mov     dword_6A9F94, eax
.text:005A38C9 75 28                                   jnz     short loc_

.rdata:00672A60 aDbghelpDll     db 'DBGHELP.DLL',0

->

.text:005A38B4 56                                      push    esi
.text:005A38B5 8B 35 A4 20 65 00                       mov     esi, ds:LoadLibraryA
.text:005A38BB 68 60 2A 67 00                          push    offset aPatchDll ; "patch.dll"
.text:005A38C0 FF D6                                   call    esi ; LoadLibraryA
.text:005A38C1 5E                                      pop esi
.text:005A38C2 E9 2A B3 07 00                          jmp start
'''
def patch():
    EP = 0x001A38B4 # 修改后的入口点
    EPOffset = 0x120
    writeBytes(EPOffset,EP.to_bytes(4,'little')) # EP: 0021EBF2h -> 005A38B4h
    targetOffset = 0x001A38C2 # 0x005A38C2 - IMAGE_BASE
    writeBytes(targetOffset,bytes([0x5E])) # pop esi
    writeBytes(targetOffset + 1,bytes([0xE9,0x2A,0xB3,0x07,0x00])) # jmp start
    DLLNameOffset = 0x00272A60 # db 'DBGHELP.DLL',0
    writeBytes(DLLNameOffset,b'patch.dll\x00')

def unpatch():
    EP = 0x0021EBF2
    EPOffset = 0x120
    writeBytes(EPOffset,EP.to_bytes(4,'little')) # EP: 005A38B4h -> 0021EBF2h
    targetOffset = 0x001A38C2 # 0x005A38C2 - IMAGE_BASE
    writeBytes(targetOffset,bytes([0x85,0xC0,0xA3,0x94,0x9F,0x6A]))
    DLLNameOffset = 0x00272A60
    writeBytes(DLLNameOffset,b'DBGHELP.DLL\x00')


if __name__ == "__main__":
    print('1. Patch\n2. Unpatch')
    code = input('Please choose an operation: ')
    if code == '1':
        patch()
    elif code == '2':
        unpatch()
    print('Success!')
```
