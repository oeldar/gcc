/* { dg-do compile } */
/* { dg-options "-G4 -mexplicit-relocs -msdata-num=7" } */

volatile int sdata_num_data = 1;
volatile int sdata_num_bss __attribute__((nocommon));

int
read_sdata_num_data (void)
{
  return sdata_num_data;
}

int
read_sdata_num_bss (void)
{
  return sdata_num_bss;
}

/* { dg-final { scan-assembler "\\.section\[ \t\]+\\.sdata_7" } } */
/* { dg-final { scan-assembler "\\.section\[ \t\]+\\.sbss_7" } } */
/* { dg-final { scan-assembler "%gp_?rel\\(sdata_num_data\\)" } } */
/* { dg-final { scan-assembler "%gp_?rel\\(sdata_num_bss\\)" } } */
