/* { dg-options "-mabi=32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Os" } { "" } } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

/* A word-aligned copy of up to MIPS_MAC_MOVE_MEM_STRAIGHT bytes should be
   expanded as straight-line code rather than as block-move loop. */
   
unsigned int a[4];
unsigned int b[4];

NOCOMPRESSION void
foo (void)
{
	__builtin_memcpy (a, b, sizeof (a));
}

/* { dg-final { scan-assembler-not "\tmemcpy" } } */
/* { dg-final { scan-assembler-not "\tbne\t" } } */
