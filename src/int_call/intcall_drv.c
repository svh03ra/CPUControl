// Author: svh03ra
// (C) 2025, All rights reserved

#include <ntddk.h>

// -----------------------------------------------------------------------------
// Declaration of external assembly routine
// This is defined in interrupt.asm and triggers a software interrupt using `int`.
// Must be built with ml64.exe for x64 targets.
extern VOID InterruptCPU(VOID);

// -----------------------------------------------------------------------------
// DriverUnload: Called when the driver is unloaded from memory.
// It's a good practice to clean up or log during driver unload.
VOID DriverUnload(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("CPUInterrupt: [INFO] Driver unloaded.\n");
}

// -----------------------------------------------------------------------------
// DriverEntry: Main entry point of the driver
// This function is executed when the driver is loaded via `sc start` or similar.
//
// In this driver, a software interrupt is triggered using the InterruptCPU() function,
// which executes an `int n` instruction. This can invoke BIOS, OS services, or faults.
//
// WARNING: This might be risky, DON'T USE WITH PHYSICAL HARDWARE!!!
// -----------------------------------------------------------------------------
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    // Set the unload routine (though interrupts may be pending)
    DriverObject->DriverUnload = DriverUnload;

    // Log and trigger software interrupt
    DbgPrint("CPUInterrupt: [WARNING] Triggering software interrupt via InterruptCPU()...\n");
    InterruptCPU();  // Assembly routine: executes int n instruction

    // May continue or trap depending on interrupt type
    return STATUS_SUCCESS;
}