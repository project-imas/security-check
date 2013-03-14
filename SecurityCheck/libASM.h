//---------------------------------------------------------------------------
// libASM.h:	Assembly language macros for setting up functions .
//---------------------------------------------------------------------------
// Create some macros to generate the start and end of my assembly functions
// that can be called from C code.
// WARNING: These functions don't allow more than 4 arguments in each function.
// For more than 4 arguments, you need a stack frame for arguments after the 4th.

#if defined(__arm__)

.macro BEGIN_FUNCTION
	.align 2			// Align the function code to a 4-byte (2^n) word boundary.
	.arm				// Use ARM instructions instead of Thumb.
	.globl _$0			// Make the function globally accessible.
	.no_dead_strip _$0	// Stop the optimizer from ignoring this function!
	.private_extern _$0
_$0:					// Declare the function.
.endmacro

.macro BEGIN_FUNCTION_THUMB
	.align 2			// Align the function code to a 4-byte (2^n) word boundary.
	.thumb				// Use THUMB-2 instrctions instead of ARM.
	.globl _$0			// Make the function globally accessible.
	.thumb_func _$0		// Use THUMB-2 for the following function.
	.no_dead_strip _$0	// Stop the optimizer from ignoring this function!
	.private_extern _$0
_$0:					// Declare the function.
.endmacro

.macro END_FUNCTION
	bx	lr				// Jump back to the caller.
.endmacro

// Store a 32-bit constant into a register.
// eg: SET_REG r1, 0x11223344
.macro SET_REG
	// Recommended for ARMv6+ because the number is stored inside the instruction:
	movw	$0, #:lower16:$1
	movt	$0, #:upper16:$1
.endmacro

//---------------------------------------------------------------------------//
.macro IOS_INIT

	// Initialize this module so it can have code that is visible from iPhone with XCode.
	.syntax unified		// Allow both ARM and Thumb-2 instructions
	.section __TEXT,__text,regular
	.section __TEXT,__textcoal_nt,coalesced
	.section __TEXT,__const_coal,coalesced
	.section __TEXT,__symbol_stub4,symbol_stubs,none,12
	.text
.endmacro

#endif