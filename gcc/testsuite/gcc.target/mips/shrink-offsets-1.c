/* { dg-do compile } */
/* { dg-options "-mips16 -mshrink-offsets isa_rev<=5 -mgp32 -fdump-rtl-all" } */
/* { dg-skip-if "requires -Os" { *-*-* } { "*" } { "-Os" } } */

int
sum_shrink_offsets (int *p)
{
  return p[33] + p[34] + p[35] + p[36]
      + p[37] + p[38] + p[39] + p[40];
}

void
store_shrink_offsets (int *p, int x)
{
  p[33] = x;
  p[34] = x + 1;
  p[35] = x + 2;
  p[36] = x + 3;
}

/* { dg-final { scan-rtl-dump "Potential savings" "shrink_offsets" } } */
/* { dg-final { scan-rtl-dump "Adjusting r" "shrink_offsets" } } */
