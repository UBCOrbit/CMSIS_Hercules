;-------------------------------------------------------------------------------
; sys_memory.asm
;
; (c) Texas Instruments 2009-2010, All rights reserved.
;

    .text
    .arm


;-------------------------------------------------------------------------------
; Initialize memory

    .def     _memoryInit_
    .asmfunc

_memoryInit_
        
        ldr   r12, regMinitGcr    ; MINITGCR register pointer 
        mov   r4, #0xA
        str   r4, [r12]
        ldr   r4, ramInitMask     ; load RAM initialization mask
        str   r4, [r12, #4]
mloop
        ldr   r5, [r12, #12]
        tst   r5, #0x100
        beq   mloop
        mov   r4, #5
        str   r4, [r12]
        bx    lr
    
ramInitMask   .word 0x1E57F
regMinitGcr   .word 0xFFFFFF5C

    .endasmfunc


    

;-------------------------------------------------------------------------------

