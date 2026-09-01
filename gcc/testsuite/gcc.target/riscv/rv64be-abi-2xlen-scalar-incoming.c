/* { dg-do compile} */
/* { dg-options "-O2 -march=rv64gc -mabi=lp64 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned long u64;
typedef unsigned __int128 u128;

/* Verify that the 2*XLEN rules are XLEN-generic rather than specific to
   RV32. A named unsigned __int128 uses significance ordering in GPRs.  */

/*
** pair_low:
**	ret
*/
u64 __attribute__ ((noipa))
pair_low (u128 x)
{
  return (u64) x;
}

/*
** pair_high:
**	mv	a0,a1
**	ret
*/
u64 __attribute__ ((noipa))
pair_high (u128 x)
{
  return (u64) (x >> 64);
}

/* With only a7 available, the low 64 bits are in a7 and the high 64 bits
   are at 0(sp)  */

/*
** split_low:
**	...
**	mv	a0,a7
**	...
**	jr	ra
*/
u64 __attribute__ ((noipa))
split_low (u64 pad0, u64 pad1, u64 pad2, u64 pad3,
           u64 pad4, u64 pad5, u64 pad6, u128 x)
{
  return (u64) x;
}

/*
** split_high:
**	...
**	ld	a0,[0-9]+\(sp\)
**	...
**	jr	ra
*/
u64 __attribute__ ((noipa))
split_high (u64 pad0, u64 pad1, u64 pad2, u64 pad3,
            u64 pad4, u64 pad5, u64 pad6, u128 x)
{
  return (u64) (x >> 64);
}

/* With no argument GPR available, normal big-endian stack layout applies.  */

/*
** stack_low:
**	...
**	ld	a0,8\(sp\)
**	...
**	ret
*/
u64 __attribute__ ((noipa))
stack_low (u64 pad0, u64 pad1, u64 pad2, u64 pad3,
           u64 pad4, u64 pad5, u64 pad6, u64 pad7, u128 x)
{
  return (u64) x;
}

/*
** stack_high:
**	...
**	ld	a0,0\(sp\)
**	...
**	ret
*/
u64 __attribute__ ((noipa))
stack_high (u64 pad0, u64 pad1, u64 pad2, u64 pad3,
           u64 pad4, u64 pad5, u64 pad6, u64 pad7, u128 x)
{
  return (u64) (x >> 64);
}
