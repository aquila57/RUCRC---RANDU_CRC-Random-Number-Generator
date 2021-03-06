/* rucrcfrac.c - random fraction generator, 0-1  Version 0.1.0        */
/* Copyright (C) 2020 aquila57 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/* This subroutine produces a uniform random fraction      */
/* from zero to one.                                       */
/* The difference between this routine and rucrcunif()     */
/* is that this routine runs 53 times slower and has       */
/* 53 bit resolution.  rucrcunif() has 32 bit resolution.  */
/* If duplicate keys in a binary tree are not an issue,    */
/* rucrcunif() may be adequate for your application.       */

#define BITS (53)

#include "rucrc.h"

double rucrcfrac(rufmt *ru)
   {
   int i;
   double frac;            /* random number from 0-1          */
   frac = 0.0;
   i = BITS;
   while (i--)
      {
      frac *= 0.5;
      if (rucrc(ru) & 1) frac += 0.5;
      } /* for each bit in the mantissa */
   return(frac);           /* return uniform random number */
   } /* rucrcfrac */
