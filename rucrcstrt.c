/* rucrcstrt.c - Extended rucrc initialization  Version 0.1.0        */
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

/***************************************************************/
/* This is the initialization routine for extended rucrc       */
/* This initialization routine is based on one seed            */
/* parameter.                                                  */
/*                                                             */
/* See rucrcinit.c for an initialization routine based         */
/* on date, time in microseconds since the epoch.              */
/*                                                             */
/* The period length of rucrc is approximates 1.2e+61036.      */
/* The period length of GSL taus2 is 3.09e+26.                 */
/***************************************************************/

#include "rucrc.h"

rufmt *rucrcstrt(unsigned int seed)
   {
   int i;                      /* loop counter */
   unsigned int *stp,*stq;     /* pointer into state array */
   rufmt *ru;                  /* rucrc structure */

   /***************************************************/
   /* allocate memory for rucrc structure */
   /***************************************************/
   ru = (rufmt *) malloc(sizeof(rufmt));
   if (ru == NULL)
      {
      fprintf(stderr,"rucrcinit: out of memory "
      "allocating rucrc structure ru\n");
      exit(1);
      } /* out of memory */
   ru->states = STATES; /* save the number of rucrc states */
   ru->maxint = MAXINT; /* maximum 32 bit integer          */

   /***************************************************/
   /* allocate memory for rucrc state array           */
   /***************************************************/
   ru->state = (unsigned int *)
      malloc(sizeof(unsigned int) * STATES);
   if (ru->state == NULL)
      {
      fprintf(stderr,"rucrcinit: out of memory "
      "allocating ru->state state array\n");
      exit(1);
      } /* out of memory */

   /***************************************************/
   /* Randomize the seeds and states                  */
   /***************************************************/
   /* initialize the RANDU states to parameter        */
   if (seed < 1 || seed > 4000000000)
      {
      fprintf(stderr,"rucrcstrt: seed %u "
         "is invalid\n", seed);
      exit(1);
      } /* invalid seed */
   ru->seed = seed;   /* initialize seed to parameter      */
   ru->crc  = MASK;            /* set to all f's     */
   bldcrctbl(ru->crctbl);

   /***************************************************/
   /* Warm up the rucrc states.                       */
   /***************************************************/
   i = 128;
   while (i--) ru->out = RND;

   /***************************************************/
   /* initialize out, prev, and prev prev             */
   /* to random values                                */
   /***************************************************/
   ru->pprev = RND;             /* set to random UINT */
   ru->prev  = RND;             /* set to random UINT */
   ru->out   = RND;             /* set to random UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ru->state;
   stq = (unsigned int *) ru->state + STATES;
   while (stp < stq)
      {
      *stp++ = RND;             /* set to random UINT */
      } /* for each member in ru->state array */

   /***************************************************/
   /* Use rucrcinit() to initialize with              */
   /* random seeds based on date & time.              */
   /***************************************************/
   /* return the rucrc structure                      */
   /***************************************************/
   return(ru);
   } /* rucrcstrt subroutine */
