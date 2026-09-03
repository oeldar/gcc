/* { dg-do compile} */
/* { dg-options "-O2 -std=c23 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned _BitInt (65) u65;
typedef unsigned _BitInt (129) u129;

/* Values wider than 2*XLEN are passed by reference. They are divided int
   2*XLEN chunks, with the most-significant chunk at the lowest address on
   a big-endian target. Each chunk itself also hase big-endian layout.  */

/* The low 32 bits of a 65-bit value are in the low word of the second
   64-bit chunk, at byte offset 12.  */

/*
** u65_low:
**	lw	a0,12\(a0\)
**	ret
*/
u32 __attribute__ ((noipa))
u65_low (u65 x)
{
  return (u32) x;
}

/* Bit 64 is in the low word of the first, most-significant chunk.  */

/*
** u65_top:
**	lw	a0,4\(a0\)
**	ret
*/
u32 __attribute__ ((noipa))
u65_top (u65 x)
{
  return (u32) (x >> 64);
}

/* A 129-bit value occupies three 64-bit chunks. Its low word is therefore
   at byte offset 20, while bit 128 remains in the first chunk.  */

/*
** u129_low:
**	lw	a0,20\(a0\)
**	ret
*/
u32 __attribute__ ((noipa))
u129_low (u129 x)
{
  return (u32) x;
}

/*
** u129_high:
**	lw	a0,4\(a0\)
**	ret
*/
u32 __attribute__ ((noipa))
u129_high (u129 x)
{
  return (u32) (x >> 128);
}
