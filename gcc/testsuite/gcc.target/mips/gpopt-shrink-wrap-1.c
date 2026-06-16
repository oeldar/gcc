/* { dg-do compile } */
/* { dg-skip-if "requires O2" { *-*-* } { "*" } { "-O2" } } */
/* { dg-skip-if "requires non-LTO" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-mabi=32 -march=mips32r2 -mno-abicalls -fno-pic -mgpopt -G8 -fno-optimize-sibling-calls -fdump-rtl-pro_and_epilogue" } */

extern int cold (int);
int small;

int
f (int x)
{
  int y = small;
  if (x == 0)
    return y + 1;

    int z = cold (x + y);
    return z + y;
}

/* { dg-final { scan-assembler "\tlw\t\\\$\[0-9\]+,%gp_rel\\(small\\)\\(\\\$28\\)" } } */
/* { dg-final { scan-rtl-dump "Performing shrink-wrapping" "pro_and_epilogue" } } */
