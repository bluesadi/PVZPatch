# PVZPatch

### PVZ环境说明
测试用的PVZ版本是**1.0.0.1051汉化２版图鉴加强版**，只要不是魔改版PVZ应该都可以用。\
下载链接：http://lonelystar.org/ResDownload/1_PC_C.htm#v1.0_2

### 使用方法
首先我们需要给 **PlantsVsZombies.exe** 打上一些补丁，使PVZ能够加载我们的DLL文件，且不影响PVZ正常加载。\
以下是给文件打补丁的代码，用Python实现：
```py
'''
PVZPatcher.py
2020/12/17 by bluesadi
用于给 PlantsVsZombies.exe 打补丁，使其能够加载我们写的 patch.dll
'''
PVZFile = open('PlantsVsZombies.exe','rb+')

def writeBytes(offset,data):
    PVZFile.seek(offset)
    PVZFile.write(data)

def patch():
    EP = 0x0021EBE7 # 修改后的入口点
    EPOffset = 0x120
    writeBytes(EPOffset,EP.to_bytes(4,'little')) # EP: 0021EBF2h -> 0021EBE7
    DLLNameOffset = 0x00272A60 # db 'DBGHELP.DLL',0
    writeBytes(DLLNameOffset,b'patch.dll\x00')
    writeBytes(EP,bytes([0x68,0x60,0x2A,0x67,0x00])) # push offset aPatchDll
    writeBytes(EP + 5,bytes([0xFF,0x15,0xA4,0x20,0X65,0x00])) # call LoadLibraryA

if __name__ == "__main__":
    patch()
    print('Success!')
```

然后将 **patch.dll** 放在和 **PlantsVsZombies.exe** 同一目录下即可。