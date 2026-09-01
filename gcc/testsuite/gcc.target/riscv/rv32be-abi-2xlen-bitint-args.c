/* { dg-do compile} */
/* { dg-options "-O2 -std=c23 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned _BitInt (33) u33;
typedef signed _BitInt (33) s33;

/* A named _BitInt wider than XLEN and no wider than 2*XLEN follows the
   scalar significance rule: low bits in a0 and high bits in a1.  */

/*
** named_u33_low:
**	ret
*/
u32 __attribute__ ((noipa))
named_u33_low (u33 x)
{
  return (u32) x;
}

/*
** named_u33_high:
**	mv	a0,a1
**	ret
*/
u32 __attribute__ ((noipa))
named_u33_high (u33 x)
{
  return (u32) (x >> 32);
}

extern void take_u33 (u33);
extern void take_s33 (s33);

/* The unused high bits are zero-extended for unsigned _BitInt and
   sign-extended for signed _BitInt.  */

/*
** pass_u33_max:
**	li	a0,-1
**	...
**	li	a1,1
**	...
**	tail	take_u33(?:@plt)?
*/
void __attribute__ ((noipa))
pass_u33_max (void)
{
  take_u33 ((u33) -1);
}

/*
** pass_s33_minus_one:
**	li	a0,-1
**	...
**	mv	a1,a0
**	...
**	tail	take_s33(?:@plt)?
*/
void __attribute__ ((noipa))
pass_s33_minus_one (void)
{
  take_s33 ((s33) -1);
}

extern void take_var_bitint (const char *, ...);

/* Variadic _BitInt values use memory-layout ordering. Thus the high word is
   in a2 and the low word in a3 after a0 has been used by the format pointer
   and a1 has been skipped for pair alignment.  */

/*
** pass_var_u33_max:
**	...
**	li	a3,-1
**	...
**	li	a2,1
**	...
**	tail	take_var_bitint(?:@plt)?
*/
void __attribute__ ((noipa))
pass_var_u33_max (void)
{
  take_var_bitint ("", (u33) -1);
}
