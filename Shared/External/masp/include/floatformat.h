/* IEEE floating point support declarations, for GDB, the GNU Debugger.
   Copyright 1991, 1994, 1995, 1997, 2000 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

#if !defined (FLOATFORMAT_H)
#define FLOATFORMAT_H 1

#include "ansidecl.h"

/* A floatformat consists of a sign bit, an exponent and a mantissa.  Once the
   bytes are concatenated according to the byteorder flag, then each of those
   fields is contiguous.  We number the bits with 0 being the most significant
   (i.e. BITS_BIG_ENDIAN type numbering), and specify which bits each field
   contains with the *_start and *_len fields.  */

/* What is the order of the bytes. */

enum floatformat_byteorders {

  /* Standard little endian byte order.
     EX: 1.2345678e10 => 00 00 80 c5 e0 fe 06 42 */

  floatformat_little,

  /* Standard big endian byte order.
     EX: 1.2345678e10 => 42 06 fe e0 c5 80 00 00 */

  floatformat_big,

  /* Little endian byte order but big endian word order.
     EX: 1.2345678e10 => e0 fe 06 42 00 00 80 c5 */

  floatformat_littlebyte_bigword

};

enum floatformat_intbit { floatformat_intbit_yes, floatformat_intbit_no };

struct floatformat
{
  enum floatformat_byteorders byteorder;
  unsigned int totalsize;	/* Total size of number in bits */

  /* Sign bit is always one bit long.  1 means negative, 0 means positive.  */
  unsigned int sign_start;

  unsigned int exp_start;
  unsigned int exp_len;
  /* Amount added to "true" exponent.  0x3fff for many IEEE extendeds.  */
  unsigned int exp_bias;
  /* Exponent value which indicates NaN.  This is the actual value stored in
     the float, not adjusted by the exp_bias.  This usually consists of all
     one bits.  */
  unsigned int exp_nan;

  unsigned int man_start;
  unsigned int man_len;

  /* Is the integer bit explicit or implicit?  */
  enum floatformat_intbit intbit;

  /* Internal name for debugging. */
  const char *name;
};

/* floatformats for IEEE single and double, big and little endian.  */

extern const struct floatformat floatformat_ieee_single_big;
extern const struct floatformat floatformat_ieee_single_little;
extern const struct floatformat floatformat_ieee_double_big;
extern const struct floatformat floatformat_ieee_double_little;

/* floatformat for ARM IEEE double, little endian bytes and big endian words */

extern const struct floatformat floatformat_ieee_double_littlebyte_bigword;

/* floatformats for various extendeds.  */

extern const struct floatformat floatformat_i387_ext;
extern const struct floatformat floatformat_m68881_ext;
extern const struct floatformat floatformat_i960_ext;
extern const struct floatformat floatformat_m88110_ext;
extern const struct floatformat floatformat_m88110_harris_ext;
extern const struct floatformat floatformat_arm_ext_big;
extern const struct floatformat floatformat_arm_ext_littlebyte_bigword;
/* IA-64 Floating Point register spilt into memory.  */
extern const struct floatformat floatformat_ia64_spill_big;
extern const struct floatformat floatformat_ia64_spill_little;
extern const struct floatformat floatformat_ia64_quad_big;
extern const struct floatformat floatformat_ia64_quad_little;

/* Convert from FMT to a double.
   FROM is the address of the extended float.
   Store the double in *TO.  */

extern void
floatformat_to_double PARAMS ((const struct floatformat *, char *, double *));

/* The converse: convert the double *FROM to FMT
   and store where TO points.  */

extern void
floatformat_from_double PARAMS ((const struct floatformat *,
				 double *, char *));

#endif	/* defined (FLOATFORMAT_H) */
