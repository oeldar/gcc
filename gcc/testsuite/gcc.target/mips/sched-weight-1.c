/* { dg-do compile } */
/* { dg-options "isa=p5600 -mtune=p5600 -mgp32 -mno-mips16 -mno-micromips -msched-weight -fdump-rtl-sched1" } */
/* { dg-skip-if "requires -O2" { *-*-* } { "*" } { "-O2" } } */
/* { dg-skip-if "requires non-LTO" { *-*-* } { "-flto" } { "" } } */

int
foo (int *p, int a, int b, int c, int d)
{
  int x0 = p[0] + a;
  int x1 = p[1] + b;
  int x2 = p[2] + c;
  int x3 = p[3] + d;
  int x4 = p[4] + a;
  int x5 = p[5] + b;
  int y0 = x0 * x3;
  int y1 = x1 * x4;
  int y2 = x2 * x5;
  return y0 + y1 + y2;
}

/* { dg-final { scan-rtl-dump {\[ x0_[^\n]*\n.*\(set \(reg:SI [0-9]+ \[ MEM\[\(int \*\)p_[^\n]* \+ 8B\] \]} "sched1" } } */
