/* { dg-do compile } */
/* { dg-options "-mips16 isa_rev<=5 -mgp32 -fdump-rtl-peephole2" } */
/* { dg-skip-if "requires -O2" { *-*-* } { "*" } { "-O2" } } */
/* { dg-skip-if "requires non-LTO" { *-*-* } { "-flto" } { "" } } */

int __RTL (startwith ("peephole2")) hi_move ()
{
(function "hi_move"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 3 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 4 (set (reg:HI $2)
        (reg:HI $3)))
      (cinsn 5 (set (reg:SI $3)
        (reg:SI $2)))
      (cinsn 6 (use (reg:SI $3)))
      (edge-to exit (flags "FALLTHRU"))
    )
  )
)
}

int __RTL (startwith ("peephole2")) qi_move ()
{
(function "qi_move"
  (insn-chain
    (block 2
      (edge-from entry (flags "FALLTHRU"))
      (cnote 3 [bb 2] NOTE_INSN_BASIC_BLOCK)
      (cinsn 4 (set (reg:QI $4)
        (reg:QI $5)))
      (cinsn 5 (set (reg:SI $5)
        (reg:SI $4)))
      (cinsn 6 (use (reg:SI $5)))
      (edge-to exit (flags "FALLTHRU"))
    )
  )
)
}

/* { dg-final { scan-rtl-dump-times "Splitting with gen_peephole2" 2 "peephole2" } } */
