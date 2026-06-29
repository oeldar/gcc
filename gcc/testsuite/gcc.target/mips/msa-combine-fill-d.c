/* { dg-do compile } */
/* { dg-options "-mno-mips16 -mfp64 -mhard-float -mmsa -fdump-rtl-combine-details" } */
/* { dg-skip-if "needs combine" { *-*-* } { "-O0" } { "" } } */

typedef long long v2i64 __attribute__((vector_size (16)));

v2i64
foo (long long x)
{
  return (v2i64) { x, x };
}

/* { dg-final { scan-rtl-dump "Instruction not appropriate for target" "combine" { target { ! mips64 } } } } */
