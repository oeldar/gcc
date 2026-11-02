/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -mbig-endian -O3" } */

/* Big-endian RVV used to be rejected outright.  Check that a vector type
   can be passed and returned with the full V extension.  */

#pragma riscv intrinsic "vector"

vfloat32m1_t
foo (vfloat32m1_t x)
{
  return x;
}
