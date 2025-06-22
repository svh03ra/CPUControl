// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in enable.asm and enables IRQs using the `sti` instruction.
// Must be built with ml64.exe for x64 targets.
extern VOID EnableCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUEnable: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, the CPU IRQs are enabled using the EnableCPU() function,
// which executes `sti`. This allows maskable interrupts to occur.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though IRQs may be enabled)
    DriverObject->DriverUnload = DriverUnload;

    // Log and enable IRQs
    DbgPrint("CPUEnable: [WARNING] Enabling CPU IRQs via EnableCPU()...\n");
    EnableCPU();  // Assembly routine: executes sti instruction

    // May continue running with interrupts enabled
    return STATUS_SUCCESS;
}