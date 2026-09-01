/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

/* A named 2*XLEN scalar split between a7 and the stack uses significanse
   ordering. The low word is in a7 and the high word is at 0(sp)  */

/*
** split_low:
**	...
**	mv	a0,a7
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
split_low (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
           u32 pad4, u32 pad5, u32 pad6, u64 x)
{
  return (u32) x;
}

/*
** split_high:
**	...
**	lw	a0,[0-9]+\(sp\)
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
split_high (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
            u32 pad4, u32 pad5, u32 pad6, u64 x)
{
  return (u32) (x >> 32);
}

/* If no argument GPR is available, the scalar is passed entirely on the
   stack in big-endian memory order: high at lower (sp) and low at high (sp)  */

/*
** stack_low:
**	...
**	lw	a0,4\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
stack_low (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
           u32 pad4, u32 pad5, u32 pad6, u32 pad7, u64 x)
{
  return (u32) x;
}

/*
** stack_high:
**	...
**	lw	a0,0\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
stack_high (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
            u32 pad4, u32 pad5, u32 pad6, u32 pad7, u64 x)
{
  return (u32) (x >> 32);
}
