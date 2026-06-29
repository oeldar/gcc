/* { dg-do compile } */
/* { dg-options "-mfunc-opt-list=func-opt-list-1.txt -mno-long-calls addressing=absolute -mno-mips16 -mno-micromips" } */

extern int long_call_func (void);
extern int normal_func (void);

int
test (void)
{
  return long_call_func () + normal_func ();
}

/* { dg-final { scan-assembler-not "\t(jals?|balc)\tlong_call_func\n" } } */
/* { dg-final { scan-assembler "\tjalr\t" } } */
/* { dg-final { scan-assembler "\t(jals?|balc)\tnormal_func\n" } } */
