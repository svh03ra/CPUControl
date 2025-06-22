; =============================================================================
; enable.asm — Simple CPU IRQ Enable Routine for x64 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; -----------------------------------------------------------------------------
;
; Target: x64 (AMD64)
; Assembler: ml64.exe (MASM for x64)
; =============================================================================
;
; This file defines:
;   - EnableCPU: enables maskable interrupts (STI)
;
; Usage:
;   extern "C" void EnableCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - STI sets the interrupt flag (IF) and enables IRQs
;   - System will begin processing maskable interrupts again
;   - Safe to use if previously disabled
;   - Should only be used in virtual machine
;
; =============================================================================

.code                    ; Begin code section

PUBLIC EnableCPU         ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID EnableCPU()
; Executes STI to enable IRQs
; ----------------------------------------------------------------------------
EnableCPU PROC
    sti                  ; Enable maskable interrupts
    ret                  ; Return (execution continues with IRQs enabled)
EnableCPU ENDP

END                      ; End of file