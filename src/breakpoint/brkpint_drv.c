// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in brkpoint.asm and triggers a breakpoint using `int 3`.
// Must be built with ml64.exe for x64 targets.
extern VOID BreakpointCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUBreak: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU is interrupted using the BreakpointCPU() function,
// which executes `int 3`. This triggers a #BP exception and may break into debugger.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though we may not reach here if system traps)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger INT3
    DbgPrint("CPUBreak: [WARNING] Triggering INT3 breakpoint via BreakpointCPU...\n");
    BreakpointCPU();  // Assembly routine: executes int 3 instruction

    // Normally unreachable if debugger catches or system bugchecks
    return STATUS_SUCCESS;
}
