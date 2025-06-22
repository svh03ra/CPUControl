// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in crash.asm and triggers an invalid opcode using `ud2`.
// Must be assembled with ml64.exe for x64 builds.
extern VOID CrashCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// Logs unload attempt. In reality, this may never execute if the CPU crashes.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUCrash: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point for the driver.
// Called when the driver is loaded via `sc start` or similar.
//
// This version triggers a CPU exception using `ud2`, which causes a #UD fault.
// This is typically unrecoverable and crashes the system.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (not likely to be reached after crash)
    DriverObject->DriverUnload = DriverUnload;

    // Log and immediately trigger invalid instruction
    DbgPrint("CPUCrash: [WARNING] Triggering invalid opcode (ud2) via CrashCPU...\n");
    CrashCPU();  // Assembly routine: emits `ud2` instruction

    // Normally never reached if system crashes
    return STATUS_SUCCESS;
}