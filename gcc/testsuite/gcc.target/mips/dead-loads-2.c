/* { dg-do compile } */
/* { dg-options "-mno-dead-loads -mno-mips16 -mno-micromips" } */
/* { dg-skip-if "" { *-*-* } { "-O0" } { "" } } */

void
foo (volatile unsigned int *p)
{
  *p;
}

/* { dg-final { scan-assembler-not "\tlw\t\\\$0," } } */
/* { dg-final { scan-assembler "\tlw\t\\\$\[1-9\]\[0-9\]*," } } */
