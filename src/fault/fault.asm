; =============================================================================
; fault.asm — Triple Fault Generator for x64 Kernel-Mode Driver
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
;   - FaultCPU: loads a null IDT and triggers INT to cause a triple fault
;
; Notes:
;   - Triple faults instantly reset on real hardware
;   - On VMs, this may shut down or reboot
;   (Example: VMware, this may trigger the "virtual CPU has entered the shutdown state" error)
;   - Should only be used in virtual machine
;
; =============================================================================

.data
EmptyIDT LABEL BYTE
    dw 0              ; Limit = 0
    dq 0              ; Base = 0 (NULL IDT)

.code

PUBLIC FaultCPU

FaultCPU PROC
    cli                       ; Disable interrupts
    lidt fword ptr [EmptyIDT] ; Load null IDT
    int 3                     ; Trigger interrupt -> causes triple fault
    hlt                       ; Just in case
    ret
FaultCPU ENDP

END