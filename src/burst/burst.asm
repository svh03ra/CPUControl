; =============================================================================
; burst.asm — Multimedia Thread Burst Simulation for x64 Kernel-Mode Driver
; Author: svh03ra
;
; (C) 2025, All rights reserved 
;
; --------------------------------------------------------------------------
; Target: x64 (AMD64)
; Assembler: ml64.exe (MASM for x64)
; Simulates a lightweight CPU workload with long loop and pause hints
; =============================================================================
;
; This file defines:
;   - BurstCPU: simulates a CPU load loop using PAUSE instructions
;
; Usage:
;   extern "C" void BurstCPU(void);
;
; Notes:
;   - This routine simulates a CPU-intensive "multimedia" workload
;     by looping with `pause` instructions for thermal testing or thread stress.
;   - Can be called from a kernel-mode thread to simulate load spikes.
;   - Safe to run on both real hardware and VMs (does NOT crash or hang system).
;   - Make sure to call it from a PASSIVE_LEVEL thread context.
;   - Should only be used in virtual machine
;
; =============================================================================


.code

PUBLIC BurstCPU

BurstCPU PROC
    mov rcx, 10000000h     ; Large iteration count
burst_loop:
    pause                  ; Equivalent to rep nop (for modern CPUs)
    dec rcx
    jnz burst_loop
    ret
BurstCPU ENDP

END