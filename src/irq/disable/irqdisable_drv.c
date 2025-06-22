// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in disable.asm and disables IRQs using the `cli` instruction.
// Must be built with ml64.exe for x64 targets.
extern VOID DisableCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUDisable: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU IRQs are disabled using the DisableCPU() function,
// which executes `cli`. This prevents maskable interrupts until re-enabled.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though IRQs may be disabled)
    DriverObject->DriverUnload = DriverUnload;

    // Log and disable IRQs
    DbgPrint("CPUDisable: [WARNING] Disabling CPU IRQs via DisableCPU()...\n");
    DisableCPU();  // Assembly routine: executes cli instruction

    // May continue running, but with interrupts disabled
    return STATUS_SUCCESS;
}