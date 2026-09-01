/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32e -mabi=ilp32e -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

/* ILP32E has six argument GPRs. With five words already in a0-a4, a named
   2 * XLEN scalar is split between a5 and the stack. Significance ordering
   puts the low word in a5 and the high word at 0(sp)  */

/*
** ilp32e_split_low:
**	...
**	mv	a0,a5
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
ilp32e_split_low (u32 pad0, u32 pad1, u32 pad2, u32 pad3, u32 pad4, u64 x)
{
  return (u32) x;
}

/*
** ilp32e_split_high:
**	...
**	lw	a0,0\(sp\)
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
ilp32e_split_high (u32 pad0, u32 pad1, u32 pad2, u32 pad3, u32 pad4, u64 x)
{
  return (u32) (x >> 32);
}

/* Once a0-a5 are occupied, the scalar is entirely on the stack in normal
   big-endian memory order.  */

/*
** ilp32e_stack_low:
**	...
**	lw	a0,4\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
ilp32e_stack_low (u32 pad0, u32 pad1, u32 pad2,
		  u32 pad3, u32 pad4, u32 pad5, u64 x)
{
  return (u32) x;
}


/*
** ilp32e_stack_high:
**	lw	a0,0\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
ilp32e_stack_high (u32 pad0, u32 pad1, u32 pad2,
		   u32 pad3, u32 pad4, u32 pad5, u64 x)
{
  return (u32) (x >> 32);
}
