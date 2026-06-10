/* { dg-do compile } */
/* { dg-options "-Os -fdump-tree-einline-details" }*/

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

/* { dg-final { scan-tree-dump "will not early inline: main/\[0-9\]*->foo/\[0-9\]*, call is cold and code would grow by" "einline" } } */
/* { dg-final { scan-tree-dump-not "Inlining foo/\[0-9\]* into main/\[0-9\]*" "einline" } } */
