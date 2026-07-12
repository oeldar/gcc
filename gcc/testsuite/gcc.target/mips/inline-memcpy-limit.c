/* { dg-options "-mabi=32 -mblockmov-limit=16" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Os" } { "" } } */
/* { dg-skip-if "" { *-*-* } { "-flto" } } */

/* -mblockmov-limit should prevent a constant-sized copy at the limit from
   being expanded inline. */
   
unsigned int a[4];
unsigned int b[4];

NOCOMPRESSION void
foo (void)
{
	__builtin_memcpy (a, b, sizeof (a));
}

/* { dg-final { scan-assembler "\tmemcpy" } } */
