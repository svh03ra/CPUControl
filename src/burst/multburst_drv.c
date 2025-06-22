// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in burst.asm and simulates a multimedia thread CPU burst.
// Must be built with ml64.exe for x64 targets.
extern VOID BurstCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUBurst: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, a high-frequency multimedia-like CPU load is triggered
// using the BurstCPU() function, which may simulate intensive thread activity.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though burst may consume CPU)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger multimedia thread burst
    DbgPrint("CPUBurst: [WARNING] Triggering Multimedia Thread Burst via BurstCPU()...\n");
    BurstCPU();  // Assembly routine: simulates CPU load or loop burst

    // May continue depending on implementation
    return STATUS_SUCCESS;
}