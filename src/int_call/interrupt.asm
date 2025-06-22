; =============================================================================
; interrupt.asm — Software Interrupt Trigger Routine for x64 Kernel-Mode Driver
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
;   - InterruptCPU: triggers a software interrupt using INT
;
; Usage:
;   extern "C" void InterruptCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - This executes a software INT (e.g., INT 0x10 for BIOS video call)
;   - Most INTs are invalid in long mode (x64), expect #GP or #UD
;   - Intended only for controlled VMs or diagnostic use
;   - Should only be used in virtual machine
;
; =============================================================================

.code                    ; Begin code section

PUBLIC InterruptCPU      ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID InterruptCPU()
; Executes INT 0x10 (BIOS video service)
; ----------------------------------------------------------------------------
InterruptCPU PROC
    int 10h              ; Software interrupt 0x10 (example only)
    ret                  ; Return (if not faulted)
InterruptCPU ENDP

END                      ; End of file