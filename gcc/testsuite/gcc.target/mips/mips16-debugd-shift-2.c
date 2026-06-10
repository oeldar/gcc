/* { dg-do compile } */
/* { dg-options "-mips16 isa_rev<=5 -mgp32 -mno-debugd -fdump-rtl-expand" } */
/* { dg-skip-if "requires -O2" { *-*-* } { "*" } { "-O2" } } */

int
foo (int a)
{
  return a << 13;
}

/* { dg-final { scan-rtl-dump-times {\(const_int 8} 1 "expand" } } */
/* { dg-final { scan-rtl-dump-times {\(const_int 5} 1 "expand" } } */
