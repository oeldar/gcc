/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

extern int tail_target (u32, u32, u32, u32, u32, u32, u32, u64);

/* The split stack piece is already et the incoming argument base. Verify
   that forwarding the unchanged argument can remain a sibling call.  */

/*
** tail_forward:
**	...
**	tail	tail_target(?:@plt)?
**	...
*/
int
tail_forward (u32 pad0, u32 pad1, u32 pad2, u32 pad3,
              u32 pad4, u32 pad5, u32 pad6, u64 x)
{
  return tail_target (pad0, pad1, pad2, pad3, pad4, pad5, pad6, x);
}
