/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

extern void var_scalar (const char *, ...);

void
call_var (u32 high, u32 low)
{
  u64 x = ((u64) high << 32) | low;
  var_scalar ("", x);
}

/* Anonymous 2 * XLEN scalars follow memory-layout ordering so that register
   spills preserve the stack layout used by va_arg.  On RV32BE, a2 is the high
   word and a3 is the low word.  */
/* { dg-final { scan-assembler {\mmv[ \t]+a2,a0} } } */
/* { dg-final { scan-assembler {\mmv[ \t]+a3,a1} } } */
/* { dg-final { scan-assembler-not {\mmv[ \t]+a2,a1} } } */
