/* { dg-do compile } */
/* { dg-options "-dp isa=p5600 -mtune=p5600 -mno-micromips -mno-mips16" } */

void
foo (void)
{
  /* Force four callee-saved GPRs to be saved and resotred. */
  asm volatile ("" ::: "$16", "$17", "$18", "$19");
}

/* The first instruction in each bonded save pair is annotated with the
   join2_load_storesi sotre alternative. */
/* { dg-final { scan-assembler-times "\tsw\t\[^\n\]*join2_load_storesi/2" 2 } } */