#include "libASM.h"

#if defined(__arm64__)

//------ AArch64 registers used:
//
// x0-x7        input/result
// x18          platform        save
// x19-x28      callee saved    save
// x29(FP)      frame pointer   save
// x30(LR)      link reg        save
//
// d8-d15       callee saved    save
//

BEGIN_FUNCTION readSys
    // I don't think this needs more registers saved/restored in prologue/epilogue?
    // Caller should have saved any needed, and sysctl will save any callee-saved.
    // x16 is assumed caller saved already
    // x4-x5 are parameter registers, and we only need to expect x0-x3 for sysctl,
    // so we should be able zero x4-x5 safely

    // prologue
    stp fp, lr, [sp, #-16]!
    add fp, sp, #0

    mov     x4, #0
    mov     x5, #0
    mov     x16, #202
    svc     #128

    //epilogue
    ldp fp, lr, [sp], #16                   // restore state

END_FUNCTION

#elif defined(__arm__)

//------ AArch32 registers used:
// r0:	arg0 & result (input & output parameters)
// r1:	arg1 (input parameter)
// r2:
// r3:
// r4:		(must restore if modified)
// r5:		(must restore if modified)
// r6:		(must restore if modified)
// r7:		* Frame Pointer in iOS (dont touch!)
// r8:		(must restore if modified)
// r9:
// r10:		(must restore if modified)
// r11:		(must restore if modified)
// r12:
// r13:		* Stack Pointer (dont touch!)
// r14:		(must restore if modified)
// r15:		* Program Counter (dont touch!)

BEGIN_FUNCTION readSys
    // ---------------
    // prolog
    // ---------------
    push	{r4,r5,r6, r7,lr}   // Save registers r4-r6 if used and Frame Pointer (r7) and Link Register (r14).
    add		r7, sp,#12          // Adjust FP to point to the saved FP (r7).
    push	{r8,r10,r11,r14}    // Save any general registers that should be preserved.
    vstmdb	sp!, {d8-d15}       // Save any VFP or NEON registers that should be preserved (S16-S31 / Q4-Q7).
    sub		sp, sp,#4           // Allocate space for some local storage (optional).

    mov     r4, #0
    mov     r5, #0
    mov     r8, #0
    mov     r9, #0

    mov     r12, #202
    svc     #128

    // ---------------
    // epilog
    // ---------------
    add		sp, sp,#4           // Deallocate space for some local storage (optional).
    vldmia	sp!, {d8-d15}       // Restore any VFP or NEON registers that should be preserved (S16-S31 / Q4-Q7).
    pop		{r8,r10,r11,r14}	// Restore any general registers that were saved.
    pop		{r4,r5,r6, r7,pc}	// Restore saved registers, the saved FP (r7), and return to the caller (saved LR as PC).

END_FUNCTION

#endif
