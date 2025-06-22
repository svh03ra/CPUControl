// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in mask.asm and triggers a Non-Maskable Interrupt (NMI).
// Must be built with ml64.exe for x64 targets.
extern VOID MaskCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUMask: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, a Non-Maskable Interrupt (NMI) is triggered using the MaskCPU()
// function, which simulates a hardware-level non-maskable interrupt.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though a fault may prevent reaching here)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger NMI
    DbgPrint("CPUMask: [WARNING] Triggering Non-Maskable Interrupt via MaskCPU()...\n");
    MaskCPU();  // Assembly routine: simulates an NMI

    // May continue or bugcheck depending on system config
    return STATUS_SUCCESS;
}