/* { dg-do compile } */
/* { dg-options "isa_rev>=6 -mno-unaligned-access" } */

char aligned2_dest[10] __attribute__ ((aligned (4)));

void
store_aligned1 (char *p)
{
  __builtin_memcpy (p, "12345", 5);
}

void
store_aligned2 (void)
{
  __builtin_memcpy (aligned2_dest + 2, "12345678", 8);
}

/* { dg-final { scan-assembler-not "\tmemcpy" } } */
/* { dg-final { scan-assembler-not "\tlhu\t" } } */
