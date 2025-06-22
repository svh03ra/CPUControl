; =============================================================================
; profault.asm — General Protection Fault Trigger Routine for x64 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; Target: x64 (AMD64)
; Assembler: ml64.exe (MASM for x64)
; =============================================================================
;
; This file defines:
;   - ProtectCPU: triggers a general protection fault (GPF)
;
; Usage:
;   extern "C" void ProtectCPU(void);
;
; Notes:
;   - This intentionally dereferences an invalid memory address (like 0x0)
;   - This will trigger a #GP or access violation in kernel-mode
;   - Should only be used in virtual machine
;
; =============================================================================

.code

PUBLIC ProtectCPU

ProtectCPU PROC
    mov rax, 0           ; Null pointer
    mov rbx, [rax]       ; Force access to invalid memory => #GP
    ret
ProtectCPU ENDP

END