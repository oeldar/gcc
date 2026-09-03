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

extern void take_var_pair (u32, ...);

/* Aggregates use memory-layout ordering for variadic as well as named
   arguments. After the marker in a0, high goes in a1 and low in a2.  */

/*
** pass_var_pair:
**	...
**	mv	a2,a1
**	mv	a1,a0
**	...
**	li	a0,0
**	tail	take_var_pair(?:@plt)?
*/
void __attribute__ ((noipa))
pass_var_pair (u32 high, u32 low)
{
  struct pair x = { high, low };
  take_var_pair (0, x);
}

/* A va_list has stack memory layout, so the lower-addressed word is high and
   the following word is low.  */

/*
** va_arg_pair_high:
**	...
**	lw	a0,0\([a-z][0-9]+\)
**	ret
*/
u32 __attribute__ ((noipa))
va_arg_pair_high (va_list ap)
{
  struct pair x = __builtin_va_arg (ap, struct pair);
  return x.high;
}

/* Exercise va_start as well. The variadic pair follows the marker in a0,
   so the register-save area must preserve a1 as high and a2 as low.  */
struct pair __attribute__ ((noipa))
va_pair_from_registers (u32 marker, ...)
{
  va_list ap;
  struct pair x;

  __builtin_va_start (ap, marker);
  x = __builtin_va_arg (ap, struct pair);
  __builtin_va_end (ap);
  return x;
}

/* { dg-final { scan-assembler {\msw[ \t]+a1,[0-9]+\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a2,[0-9]+\(sp\)} } } */
