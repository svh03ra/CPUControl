// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in loop.asm and traps the CPU in an infinite loop.
// Must be built with ml64.exe for x64 targets.
extern VOID LoopCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPULoop: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU is trapped using the LoopCPU() function,
// which executes an infinite loop. On real hardware, this causes a full hang.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though we may not reach here if loop is infinite)
    DriverObject->DriverUnload = DriverUnload;

    // Log and enter infinite loop
    DbgPrint("CPULoop: [WARNING] Entering infinite loop via LoopCPU...\n");
    LoopCPU();  // Assembly routine: infinite loop

    // Normally unreachable if CPU is looping
    return STATUS_SUCCESS;
}