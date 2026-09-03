/* { dg-do compile } */
/* { dg-options "-O2 -march=rv32gc -mabi=ilp32 -mbig-endian" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" } } */
/* { dg-final { check-function-bodies "**" "" } } */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct one_byte
{
  u8 value;
};

struct two_halves
{
  u16 high;
  u16 low;
};

struct two_bytes
{
  u8 first;
  u8 second;
};

struct __attribute__ ((packed)) five_bytes
{
  u32 first;
  u8 second;
};

struct padded
{
  u8 first;
  u32 second;
};

/* An aggregate smaller than XLEN is right-justified in its argument register
   on a big-endian target. Value is therefore in bits 7:0.  */

/*
** one_byte_value:
**	andi	a0,a0,0xff
**	ret
*/
u32 __attribute__ ((noipa))
one_byte_value (struct one_byte x)
{
  return x.value;
}

/* A four-byte aggregate is laid out in a0 exactly as in big-endian memory.  */

/*
** two_halves_high:
**	...
**	lhu	a0,12\(sp\)
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
two_halves_high (struct two_halves x)
{
  return x.high;
}

/*
** two_halves_low:
**	...
**	lhu	a0,14\(sp\)
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
two_halves_low (struct two_halves x)
{
  return x.low;
}

/* Partial-word aggregates are right-justified, while their fields retain
   big-endian memory order within the useful part of the register.  */

/*
** two_bytes_first:
**	...
**	slli	a0,a0,16
**	srli	a0,a0,24
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
two_bytes_first (struct two_bytes x)
{
  return x.first;
}

/*
** two_bytes_second:
**	...
**	andi	a0,a0,0xff
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
two_bytes_second (struct two_bytes x)
{
  return x.second;
}

/* A packed five-byte aggregate has a full first chunk in a0. The first byte
   of its partial second chunk is at the lower memory address and therefore
   occupies the most-significant byte of a1.  */

/*
** five_bytes_first:
**	...
**	jr	ra
**	...
*/
u32 __attribute__ ((noipa))
five_bytes_first (struct five_bytes x)
{
  return x.first;
}

/*
** five_bytes_second:
**	...
**	srli	a0,a1,24
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
five_bytes_second (struct five_bytes x)
{
  return x.second;
}


/* Internal structure padding places second at offset four, so the two fields
   arrive in different GPRs. First remains in the most-significant byte of
   the lower-addressed word.  */

/*
** padded_first:
**	...
**	srli	a0,a0,24
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
padded_first (struct padded x)
{
  return x.first;
}

/*
** padded_second:
**	...
**	mv	a0,a1
**	...
**	jr	ra
*/
u32 __attribute__ ((noipa))
padded_second (struct padded x)
{
  return x.second;
}
