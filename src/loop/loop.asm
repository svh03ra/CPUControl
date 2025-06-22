; =============================================================================
; loop.asm — Simple Infinite CPU Loop for x64 Kernel-Mode Driver
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
;   - LoopCPU: traps the CPU in an infinite loop (jmp $)
;
; Usage:
;   extern "C" void LoopCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - JMP $ causes the CPU to execute the same instruction endlessly
;   - Effectively hangs the system core if not preempted
;   - Use only in virtual machine or debugging testbeds
;   - Should only be used in virtual machine
;
; =============================================================================

.code                    ; Begin code section

PUBLIC LoopCPU           ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID LoopCPU()
; Executes infinite loop using `jmp $`
; ----------------------------------------------------------------------------
LoopCPU PROC
    jmp $
LoopCPU ENDP

END                      ; End of file