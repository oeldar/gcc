/* { dg-do compile } */
/* { dg-options "-G4 -mexplicit-relocs -msdata-num=5 -msdata-opt-list=${srcdir}/gcc.target/mips/sdata-opt-list-1.lst" } */

int sdata_opt_list_data[2] = {1, 2};
int sdata_opt_list_other[2] = {3, 4};

int
read_sdata_opt_list_data (void)
{
  return sdata_opt_list_data[0];
}

int
read_sdata_opt_list_other (void)
{
  return sdata_opt_list_other[0];
}

/* { dg-final { scan-assembler "\\.section\[ \t\]+\\.sdata_5" } } */
/* { dg-final { scan-assembler "%gp_?rel\\(sdata_opt_list_data\\)" } } */
/* { dg-final { scan-assembler-not "%gp_?rel\\(sdata_opt_list_other\\)" } } */
