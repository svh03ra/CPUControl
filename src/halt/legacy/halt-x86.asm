; =============================================================================
; halt.asm — Simple CPU Halt Routine for x86 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; -----------------------------------------------------------------------------
;
; Target: x86 (IA-32)
; Assembler: ml.exe (MASM for x86)
; =============================================================================
;
; This file defines:
;   - _HaltCPU@0 : stdcall-decorated export (C symbol for __stdcall void HaltCPU())
;
; Usage:
;   extern "C" __stdcall void HaltCPU(void);  // In C code
;
; Notes:
;   - Uses stdcall calling convention, name is decorated as _HaltCPU@0
;   - Must match function prototype in driver C code
;   - Will freeze system or halt VCPU in VM environments
;   - Should only be used in virtual machine
;
; =============================================================================

.386                    ; Enable 80386 instruction set
.model flat, stdcall    ; Flat memory model, stdcall convention

.code                   ; Begin code section

PUBLIC _HaltCPU@0       ; Export symbol with stdcall name decoration

; -----------------------------------------------------------------------------
; VOID __stdcall HaltCPU()
; Disables interrupts and halts the CPU (indefinitely)
; -----------------------------------------------------------------------------
_HaltCPU@0 PROC
    cli                 ; Disable interrupts
    hlt                 ; Halt CPU
    ret                 ; Return (should never be reached after hlt)
_HaltCPU@0 ENDP

END                     ; End of file