/* { dg-do compile} */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned int u32;
typedef unsigned long long u64;
typedef __builtin_va_list va_list;

/* A va_list is formatted like the stack. Thus an RV32BE u64 has its high
   word at the lower address and its low word at the higher address. */

/*
** va_arg_u64_high:
**	...
**	lw	a0,0\([a-z][0-9]+\)
**	ret
*/
u32 __attribute__ ((noipa))
va_arg_u64_high (va_list ap)
{
  u64 x = __builtin_va_arg (ap, u64);
  return (u32) (x >> 32);
}

/*
** va_arg_u64_low:
**	...
**	lw	a0,4\([a-z][0-9]+\)
**	ret
*/
u32 __attribute__ ((noipa))
va_arg_u64_low (va_list ap)
{
  u64 x = __builtin_va_arg (ap, u64);
  return (u32) x;
}

/* va_arg first aligns AP to an 8-byte boundary. The argument following the
   u64 therefore starts eight bytes after the aligned address. */

/*
** va_arg_after_u64:
**	...
**	lw	a0,8\([a-z][0-9]+\)
**	ret
*/
u32 __attribute__ ((noipa))
va_arg_after_u64 (va_list ap)
{
  (void) __builtin_va_arg (ap, u64);
  return __builtin_va_arg (ap, u32);
}

/* Exercise va_start as well as va_arg. With only marker named, the first
   u64 is reconstructed from the register save area. */
u64 __attribute__ ((noipa))
va_from_registers (u32 marker, ...)
{
  va_list ap;
  u64 x;

  __builtin_va_start (ap, marker);
  x = __builtin_va_arg (ap, u64);
  __builtin_va_end (ap);
  return x;
}

/* Seven named words leave only a7 unused. Aligning the va_list for the u64
   skips the saved a7 slot and selects the first argument at entry sp. */
u64 __attribute__ ((noipa))
va_from_stack (u32 pad0, u32 pad1, u32 pad2, u32 pad3, u32 pad4, u32 pad5, u32 pad6, ...)
{
  va_list ap;
  u64 x;

  __builtin_va_start (ap, pad6);
  x = __builtin_va_arg (ap, u64);
  __builtin_va_end (ap);
  return x;
}

/* Both wrappers must construct a register save area. In particular, the
   first wrapper saves the aligned pair a2/a3 and the second saves a7 before
   va_arg skips that slot. */
/* { dg-final { scan-assembler {\msw[ \t]+a2,[0-9]+\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a3,[0-9]+\(sp\)} } } */
/* { dg-final { scan-assembler {\msw[ \t]+a7,[0-9]+\(sp\)} } } */
