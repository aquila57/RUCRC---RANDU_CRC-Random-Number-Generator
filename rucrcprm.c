/* rucrcprm.c - random rucrc parms Version 0.1.0                     */
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

/**********************************************************/
/* void rucrcprm(unsigned int *list)                      */
/* This subroutine calculates one large prime number      */
/* at random.  The number may be used to                  */
/* initialize rucrcstrt.c for regression testing.         */
/* This subroutine has one parameter.                     */
/**********************************************************/

#include "rucrc.h"

/* This subroutine returns a prime number */

unsigned int rucrcprm(void)
   {
   int prm;          /* candidate prime */
   int j;            /* divisor to test prime */
   int root;         /* square root of candidate */
   int rem;          /* remainder */
   double dblroot;   /* square root of candidate */
   rufmt *ru;          /* rucrc structure */
   /* rucrc initialization based on date/time */
   ru = (rufmt *) rucrcinit();   /* initialize rucrc */
   /* select a 30 bit random number */ 
   /* that number will be tested to be prime */
   /* the number chosen is odd and greater than 2 */
   prm = (rucrcpwr(ru,30) | 1) + 2;
   rem = 0;          /* initialize remainder */
   /***********************************************************/
   /* if number is not divisible by 1 or itself, it is prime. */
   /* if number is not prime, choose next higher odd number.  */
   /***********************************************************/
   while (!rem)      /* loop until prime number found */
      {
      /* calculate square root of candidate */
      dblroot = sqrt((double) prm) + 1.0;
      root = (int) floor(dblroot);
      j = 3;
      /* divide by all odd numbers <= square root */
      while (j <= root)     /* divide by odd numbers */
         {
         rem = prm % j;     /* is candidate divisible? */
         if (!rem) break;   /* yes, pick next candidate */
         j += 2;            /* no, divide by next odd number */
         } /* for each divisor */
      prm += 2;             /* pick next candidate prime */
      } /* for each candidate prime */
   free(ru->state);            /* free rucrc structure */
   free(ru);                   /* free rucrc structure */
   return(prm);
   } /* rucrcprm subroutine */
