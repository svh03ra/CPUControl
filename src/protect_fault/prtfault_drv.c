// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in protect.asm and triggers a General Protection Fault.
// Must be built with ml64.exe for x64 targets.
extern VOID ProtectCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUProtect: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, a General Protection Fault is triggered using the ProtectCPU()
// function, which executes a privilege or memory violation.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though a fault may prevent reaching here)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger general protection fault
    DbgPrint("CPUProtect: [WARNING] Triggering General Protection Fault via ProtectCPU()...\n");
    ProtectCPU();  // Assembly routine: triggers GP fault

    // May continue or bugcheck depending on execution context
    return STATUS_SUCCESS;
}