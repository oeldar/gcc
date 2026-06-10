/* { dg-do compile } */
/* { dg-options "-Os -fdump-tree-einline-details --param early-inlining-insns-cold=32" }*/

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

/* { dg-final { scan-tree-dump "Inlining foo/\[0-9]* into main/\[0-9]*" "einline" } } */
/* { dg-final { scan-tree-dump-not "will not early inline: main/\[0-9]* -> foo/\[0-9]*, call is cold and code would grow by" "einline" } } */
