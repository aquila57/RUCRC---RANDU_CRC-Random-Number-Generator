/* rucrc.c - random number generator Version 0.1.0                    */
/* Copyright (C) 2021 aquila57 at github.com                         */

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

#include "rucrc.h"

unsigned int rucrc(rufmt *ru)
   {
   unsigned int *p;           /* state array pointer */
   unsigned int tmp;          /* used for Bays-Durham shuffle */
   /**********************************************************/
   /* The offset into the state array is not related         */
   /* to the current state.                                  */
   /**********************************************************/
   /* calculate a 14-bit offset into the state array         */
   /* See the Bays-Durham shuffle below.                     */
   ru->ofst  = ru->pprev >> 18;   /* offset into state array */
   ru->pprev = ru->prev;   /* prev prev <== prev             */
   ru->prev  = ru->out;    /* prev <== current               */
   /* calculate new current state                            */
   /* using the taus algorithm                               */
   /* The TAUS macro is in rucrc.h                           */
   /* XOR the two previous outputs with the current output   */
   ru->out = RND;

   /********************************************************/
   /* Bays-Durham shuffle of state array                   */
   /* 16384! = 1.2e+61036 base 10                          */
   /* The period length of the state array is theoretical  */
   /* and cannot be proven with empirical testing.         */
   /********************************************************/
   /* point to a state array element                       */
   p       = (unsigned int *) ru->state + ru->ofst;
   /* swap the current output with the member of the state array */
   tmp     = *p;
   *p      = ru->out;
   ru->out = tmp;
   /********************************************************/
   /* return the output of the rucrc cycle after the swap  */
   return(ru->out);
   } /* rucrc subroutine */
