/* { dg-do compile } */
/* { dg-options "-mdead-loads -mno-mips16 -mno-micromips" } */
/* { dg-skip-if "" { *-*-* } { "-O0" } { "" } } */

void
foo (volatile unsigned int *p)
{
  *p;
}

/* { dg-final { scan-assembler "\tlw\t\\\$0," } } */
