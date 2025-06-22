; ============================================================================
; halt.asm — Simple CPU Halt Routine for x64 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; ----------------------------------------------------------------------------
;
; Target: x64 (AMD64)
; Assembler: ml64.exe (MASM for x64)
; ============================================================================
;
; This file defines:
;   - HaltCPU: disables interrupts and halts the processor
;
; Usage:
;   extern "C" void HaltCPU(void);    // In C or C++
;
; Notes:
;   - This uses the Microsoft x64 calling convention (no decorations needed)
;   - Interrupts are disabled via CLI before halting shouldn't run on real hardware
;   - Will freeze system in most real environments
;   - Should only be used in virtual machine
;
; ============================================================================

.code                    ; Begin code section

PUBLIC HaltCPU           ; Export symbol as-is (x64 uses undecorated names)

; ----------------------------------------------------------------------------
; VOID HaltCPU() (as in the driver code)
; Disables interrupts and halts CPU execution indefinitely
; ----------------------------------------------------------------------------
HaltCPU PROC
    cli                  ; Clear interrupt flag — disable all maskable interrupts
    hlt                  ; Halt the processor — execution stops until NMI/reset
    ret                  ; Return (in practice, never reached after hlt)
HaltCPU ENDP

END                      ; End of file