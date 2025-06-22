# CPU Control

This kernel-mode driver allows you to trigger and test various CPU exception states.


## ❓ What are exception modes?

These are special CPU states triggered by faults or instructions.
Here are some examples:
- **Triple Fault**: Forces a full system reset by loading a null IDT and triggering an interrupt. Often used to intentionally crash the system.
- **Halt**: Uses the `hlt` instruction to freeze the CPU indefinitely. No recovery occurs unless an external interrupt is received.
- **Invalid Opcode**: Executes the `ud2` instruction to trigger an undefined instruction exception, typically resulting in a BSOD.
- **General Protection Fault**: Triggers a #GP fault by misusing segment registers or accessing invalid memory.
- **Breakpoint**: Triggers an `int 3` software breakpoint, useful for debugging but can crash the system if unhandled.
- **Interrupt Call**: Manually invokes a software interrupt (e.g. `int 1`, `int 2`), which may be invalid or cause faults depending on handler availability.
- **IRQ (Interrupt Request)**: Simulates a hardware interrupt request signal; response depends on the configured interrupt table and system handlers.
- **Non-Maskable Interrupt (NMI)**: Sends a non-maskable interrupt, typically used for system diagnostics, watchdogs, or emergency handling.
- **Infinite Loop**: Uses `jmp $` to lock the CPU in a tight loop without pause, which may freeze a core or soft-lock the system.

**BONUS:** 
- **Thread Burst**: Similar to Loop Stall but structured to simulate multimedia-style CPU bursts using `pause` for stress-testing.

## ⚠️ WARNING:

**Please DO NOT run this on real hardware**, it might cause permanent damage.  
I'm not responsible, if you ruin on your personal device whatever you do...

**USE AT YOUR OWN RISK!!!**
Take this seriously, I strongly recommend testing in a **Virtual Machine** (such as VMware / VirtualBox).

#

## 🔧 Build Instructions:

These steps will help you build the project. Let's get started to follow the steps:


### 1. Requirements:

- **Windows 10 (Version 2004) or later**
- **Visual Studio Build Tools 2019 or 2022**
- **Windows Driver Kit (WDK) 10.0.19041.0** or later  
- **MASM** - included with Visual Studio for x64 assembly

**In Legacy:**

- **WDK 7.1.0**: This version supports older systems like Windows XP and Vista.  
  Navigate to the `legacy` folder and read the included README for build instructions.


### 2. Setup:

You need to **download and install** the **WDK (10.0.19041.0)** along with the matching Windows SDK from the official [Microsoft SDK Archive](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive) to ensure both the WDK and SDK versions match.


**🔧 Manually Set Environment Variables**:

You can set these system-wide using Control Panel, or:

1. Press `Win + R`, type: `SystemPropertiesAdvanced`
2. Click **Environment Variables**
3. Under **System variables**, click **New** (or Edit exists)

Add the following:

`INCLUDE`:

```
C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\km
```

`LIB`:

```
C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\km\x64
```

Add Visual Studio build tools to your `PATH` (Optional):
```
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\<version>\bin\Hostx64\x64
```

_(Replace <version> with your installed MSVC version, e.g. `14.35.32215`)_

#

Next, you'll need to build the driver tools program.  
Go to the `build` folder, it contains the tool's source code. Follow the instructions in the README to compile it.

Once compiled, run the driver tool to build your driver that's it!
