#include "libASM.h"

//------ ARM registers used:
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
//

#if defined(__arm__)

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