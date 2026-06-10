/* { dg-do compile } */
/* { dg-options "-Os -fno-early-inlining -fno-partial-inlining -fno-ipa-cp -fdump-ipa-inline-details --param max-inline-insns-small-and-cold=32" }*/

volatile int v;

int
foo (int x)
{
  v += x;
  v += 1;
  return v;
}

int
main (int argc, char **argv)
{
  return foo(argc);
}

/* { dg-final { scan-ipa-dump "Inlined foo/\[0-9\]* into main/\[0-9\]*" "inline" } } */
/* { dg-final { scan-ipa-dump-not "not inlinable: main/\[0-9\]* -> foo/\[0-9\]*, call is unlikely and code size would grow" "inline" } } */
