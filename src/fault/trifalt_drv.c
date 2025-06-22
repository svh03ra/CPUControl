// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in tripfault.asm and causes a triple fault by invalid IDT.
// Must be built with ml64.exe for x64 targets.
extern VOID FaultCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUTrip: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU is triggered into a triple fault using FaultCPU().
// This loads a null IDT and forces an INT, causing CPU to reset or halt.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though we may not reach here if system resets)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger triple fault
    DbgPrint("CPUTrip: [WARNING] Triggering triple fault via FaultCPU()...\n");
    FaultCPU();  // Assembly routine: loads null IDT and triggers interrupt

    // Normally unreachable if system resets
    return STATUS_SUCCESS;
}