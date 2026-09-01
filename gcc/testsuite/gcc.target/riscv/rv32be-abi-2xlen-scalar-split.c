/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

extern void named_odd_pair (u32, u64);
extern void named_split (u32, u32, u32, u32, u32, u32, u32, u64);
extern void named_stack (u32, u32, u32, u32, u32, u32, u32, u32, u64);


void
call_named_odd_pair (u32 high, u32 low)
{
  named_odd_pair (0, ((u64) high << 32) | low);
}

void
call_named_split (u32 high, u32 low)
{
  named_split (0, 1, 2, 3, 4, 5, 6, ((u64) high << 32) | low);
}

void
call_named_stack (u32 high, u32 low)
{
  named_stack (0, 1, 2, 3, 4, 5, 6, 7, ((u64) high << 32) | low);
}

/* With only a7 free, the low word goes in a7 and the high word goes at
   0(sp)  */
/* { dg-final { scan-assembler {\mmv[ \t]+a2,a0} } } */
/* { dg-final { scan-assembler-not {\mmv[ \t]+a2,a1} } } */

/* { dg-final { scan-assembler {\mmv[ \t]+a7,a1} } } */
/* { dg-final { scan-assembler-not {\mmv[ \t]+a7,a0} } } */

/* { dg-final { scan-assembler {\msw[ \t]+a1,4\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a0,0\(sp\)} } } */
/* { dg-final { scan-assembler-not {\msw[ \t]+a1,0\(sp\)} } } */
