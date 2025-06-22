; =============================================================================
; disable.asm — Simple CPU IRQ Disable Routine for x64 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; -----------------------------------------------------------------------------
;
; Target: x64 (AMD64)
; Assembler: ml64.exe (MASM for x64)
; =============================================================================
; This file defines:
;   - DisableCPU: disables maskable interrupts (CLI)
;
; Usage:
;   extern "C" void DisableCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - CLI clears the interrupt flag (IF) and disables IRQs shouldn't run on real hardware
;   - System continues running but won't respond to most interrupts
;   - Should only be used in virtual machine
; =============================================================================

.code                    ; Begin code section

PUBLIC DisableCPU        ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID DisableCPU()
; Executes CLI to disable IRQs
; ----------------------------------------------------------------------------
DisableCPU PROC
    cli                  ; Disable maskable interrupts
    ret                  ; Return (execution continues without IRQs)
DisableCPU ENDP

END                      ; End of file