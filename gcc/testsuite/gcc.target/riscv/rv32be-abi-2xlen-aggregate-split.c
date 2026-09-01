/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */

typedef unsigned int u32;
struct pair
{
  u32 high;
  u32 low;
};

extern void named_aggregate_split (u32, u32, u32, u32, u32, u32, u32, struct pair);

void call_named_aggregate_split (u32 high, u32 low)
{
  struct pair x = { high, low };
  named_aggregate_split (0, 1, 2, 3, 4, 5, 6, x);
}

volatile u32 sink_aggregate_split[2];

void
consume_named_aggregate_split (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
                               u32 pad4, u32 pad5, u32 pad6, struct pair x)
{
  sink_aggregate_split[0] = x.high;
  sink_aggregate_split[1] = x.low;
}

/* Aggregates retain memory-layout ordering. With only a7 free, the first
   word in memory (high) goes in a7 and the second word (low) goes at 0(sp)  */

/* { dg-final { scan-assembler {\mmv[ \t]+a7,a0} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a1,0\(sp\)} } } */
/* { dg-final { scan-assembler-not {\mmv[ \t]+a7,a1} } } */
/* { dg-final { scan-assembler-not {\msw[ \t]+a0,0\(sp\)} } } */

/* The callee must likewise interpret a7 as the first aggregate word.  */
/* { dg-final { scan-assembler {\msw[ \t]+a7,(sink_aggregate_split,|0\()} } } */
/* { dg-final { scan-assembler-not {\msw[ \t]+a7,(sink_aggregate_split\+4|4\()} } } */
