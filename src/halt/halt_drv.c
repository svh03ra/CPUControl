// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in halt.asm and halts the CPU using `cli` + `hlt`.
// Must be built with ml64.exe for x64 targets.
extern VOID HaltCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUHalt: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU is immediately halted using the HaltCPU() function,
// which executes `cli` and `hlt`. On real hardware, this will freeze the CPU.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though we never get there due to halt)
    DriverObject->DriverUnload = DriverUnload;

    // Log and immediately halt the CPU
    DbgPrint("CPUHalt: [WARNING] Halting CPU now (via HaltCPU)...\n");
    HaltCPU();  // Assembly routine: disables interrupts and halts execution

    // Normally unreachable if CPU is halted
    return STATUS_SUCCESS;
}