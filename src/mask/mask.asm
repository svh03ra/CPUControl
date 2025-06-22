; =============================================================================
; mask.asm — Non-Maskable Interrupt (NMI) Trigger Routine for x64 Kernel-Mode Driver
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
;   - MaskCPU: simulates or attempts to trigger an NMI (non-maskable interrupt)
;
; Usage:
;   extern "C" void MaskCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - Real NMIs are triggered via hardware, not software.
;   - This simulates NMI-like behavior (e.g., invalid NMI vector access).
;   - May cause system instability or bugcheck in kernel-mode.
;   - Should only be used in virtual machine
;
; =============================================================================

.code                    ; Begin code section

PUBLIC MaskCPU           ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID MaskCPU()
; Simulates a non-maskable interrupt (cannot trigger true NMI via software)
; ----------------------------------------------------------------------------
MaskCPU PROC
    int 2                ; INT 2 is reserved for NMI on x86 (will fault in long mode)
    ret                  ; Return (usually never reached)
MaskCPU ENDP

END                      ; End of file