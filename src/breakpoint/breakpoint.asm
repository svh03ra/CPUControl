; =============================================================================
; brkpoint.asm — Simple CPU Breakpoint Trigger for x64 Kernel-Mode Driver
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
;   - BreakpointCPU: triggers a breakpoint interrupt (INT3)
;
; Usage:
;   extern "C" void BreakpointCPU(void);   // In C or C++ kernel-mode driver
;
; Notes:
;   - INT3 (opcode 0xCC) triggers a breakpoint exception (#BP)
;   - May break into kernel debugger or cause bugcheck (0x80000003)
;   - Should only be used in virtual machine
;
; =============================================================================

.code                    ; Begin code section

PUBLIC BreakpointCPU     ; Exported symbol name (no decorations in x64)

; ----------------------------------------------------------------------------
; VOID BreakpointCPU()
; Executes INT3, which causes a breakpoint exception (#BP)
; ----------------------------------------------------------------------------
BreakpointCPU PROC
    int 3                ; INT3 instruction (breakpoint)
    ret                  ; Return (usually never reached if debugger traps)
BreakpointCPU ENDP

END                      ; End of file