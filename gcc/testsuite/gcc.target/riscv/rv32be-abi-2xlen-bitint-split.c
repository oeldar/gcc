/* { dg-do compile} */
/* { dg-options "-O2 -std=c23 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned _BitInt (33) u33;

/* _BitInt types wider than XLEN and no wider than 2 * XLEN follow the
   2 *  XLEN scalar rules. With only a7 available, the low word is in a7
   and the zero-extended high word is at 0(sp).  */

/*
** bitint_split_low:
**	...
**	mv	a0,a7
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
bitint_split_low (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
		  u32 pad4, u32 pad5, u32 pad6, u33 x)
{
  return (u32) x;
}

/*
** bitint_split_high:
**	...
**	lw	a0,0\(sp\)
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
bitint_split_high (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
		   u32 pad4, u32 pad5, u32 pad6, u33 x)
{
  return (u32) (x >> 32);
}

