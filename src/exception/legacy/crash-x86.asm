; =============================================================================
; crash.asm — Simple CPU Crash Routine for x64 Kernel-Mode Driver
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
;   - CrashCPU: triggers an invalid instruction (UD2)
;
; Usage:
;   extern "C" void CrashCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - UD2 is a guaranteed invalid opcode defined by Intel to raise #UD
;   - Causes a system crash (bugcheck) in kernel-mode
;   - Should only be used in virtual machine
; =============================================================================

.code                    ; Begin code section

PUBLIC CrashCPU          ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID CrashCPU()
; Executes UD2, which causes an invalid opcode exception (#UD)
; ----------------------------------------------------------------------------
CrashCPU PROC
    db 0Fh, 0Bh          ; Emit UD2 instruction manually (Intel reserved invalid opcode)
    ret                  ; Return (usually never reached)
CrashCPU ENDP

END                      ; End of file