/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef __builtin_va_list va_list;

struct pair
{
  u32 high;
  u32 low;
};

/* With all GPRs occupied, an aggregate is passed entirely on the
   stack. Memory-layout ordering puts high at 0(sp) and low at 4(sp).  */

/*
** aggregate_stack_high:
**	lw	a0,0\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
aggregate_stack_high (u32 pad0, u32 pad1, u32 pad2, u32 pad3, u32 pad4,
		      u32 pad5, u32 pad6, u32 pad7, struct pair x)
{
  return x.high;
}

/*
** aggregate_stack_low:
**	lw	a0,4\(sp\)
**	ret
*/
u32 __attribute__ ((noipa))
aggregate_stack_low (u32 pad0, u32 pad1, u32 pad2, u32 pad3, u32 pad4,
		     u32 pad5, u32 pad6, u32 pad7, struct pair x)
{
  return x.low;
}

extern void take_stack_pair (u32, u32, u32, u32, u32, u32, u32, u32, struct pair);

void __attribute__ ((noipa))
pass_stack_pair (u32 high, u32 low)
{
  struct pair x = { high, low };
  take_stack_pair (0, 1, 2, 3, 4, 5, 6, 7, x);
}

/* The caller must create the same big-endian stack image.  */
/* { dg-final { scan-assembler {\msw[ \t]+a0,0\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a1,4\(sp\)} } } */
