/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */

typedef unsigned int u32;
typedef unsigned long long u64;

extern void var_stack (u32, u32, u32, u32, u32, u32, u32, ...);

void
call_var_stack (u32 high, u32 low, u32 next)
{
  u64 x = ((u64) high << 32) | low;

  var_stack (0, 1, 2, 3, 4, 5, 6, x, next);
}

/* The seven named arguments occupy a0-a6. An anonymous 2*XLEN argument
   requires an aligned register pair, so it cannot use a7 and is passed
   entirely on the stack. Variadic arguments use memory-layout ordering:
   the high word is at 0(sp) and the low word is at 4(sp).  */

/* { dg-final { scan-assembler {\msw[ \t]+a0,0\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a1,4\(sp\)} } } */

/* Once a variadic argument has been passed on the stack, all following
   arguments are passed there too.  */

/* { dg-final { scan-assembler {\msw[ \t]+a2,8\(sp\)} } } */
