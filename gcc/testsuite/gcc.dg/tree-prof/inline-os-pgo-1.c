/* { dg-options "-Os -fno-early-inlining -fno-partial-inlining -fno-ipa-cp -fdump-ipa-inline-details" } */

volatile unsigned int value;

unsigned int
callee (unsigned int x)
{
	x ^= x << 3;
	x += x >> 2;
	value += x;
	value ^= x + 1;
	return value;
}

__attribute__ ((noinline, noclone))
unsigned int
caller (unsigned int x)
{
	unsigned int y = callee (x);
	return y + x;
}

int
main (void)
{
        unsigned int i;

        for (i = 0; i < 100000; ++i)
                value = caller (i & 7);
        return 0;
}

/* { dg-final-use-not-autofdo { scan-ipa-dump "Inlined callee/.* into caller/" "inline" } } */
