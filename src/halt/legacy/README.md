# For Legacy:

**This uses WDK 7.1.0 for 32-bit driver builds. (NOT TESTED YET)**

#

### You need to compile with these commands (x86 WDK Build CMD):

```
cl /nologo /D__KERNEL__ /D__i386__ /I%WINDDK%\inc\ddk /I%WINDDK%\inc\wxp /I%WINDDK%\inc\crt \
    /I%WINDDK%\inc /I. /c [driver .c file here]

ml /nologo /c /coff [.asm file here]

link /nologo /subsystem:native /machine:x86 /entry:DriverEntry \
    /out:[driver's name here].sys [driver's name here].obj [assembly's name here].obj \
    /libpath:%WINDDK%\lib\wxp\i386 ntoskrnl.lib hal.lib
```


I'm planning to add a few trigger modes soon, it's still a work in progress.