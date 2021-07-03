/* rucrcdspl.c - rucrc RNG Display the State  Version 0.1.0          */
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

/* Display the state of the rucrc generator, including the current   */
/* 32 bit seed, previous, prior-previous, out,                       */
/* and the 16384 word array for the Bays-Durham shuffle.             */
/* Output of this subroutine is to stderr.                           */

#include "rucrc.h"

void rucrcdspl(rufmt *ru, int option)
   {
   /*****************************************************/
   /* Print rucrc state to stderr                       */
   /* If option is not zero, print entire state array   */
   /*****************************************************/
   fprintf(stderr,"seed %08x ", ru->seed);
   fprintf(stderr,"crc %08x ", ru->crc);
   fprintf(stderr,"rucrc output %08x\n", ru->out);
   fprintf(stderr,"previous out %08x ", ru->prev);
   fprintf(stderr,"prior-previous out %08x ", ru->pprev);
   fprintf(stderr,"offset %d\n", ru->ofst);
   if (!option)
      {
      int i;
      unsigned int *p,*q;
      i = 0;
      p = (unsigned int *) ru->state;
      q = (unsigned int *) ru->state + STATES;
      fprintf(stderr,"State array:\n");
      while (p < q)
         {
         fprintf(stderr,"%08x ", *p++);
	 i++;
	 if (i >= 8)
	    {
	    fprintf(stderr,"\n");
	    i = 0;
	    } /* end of line */
	 } /* for each word in the state array */
      if (i) fprintf(stderr,"\n");
      } /* if display the state array */
   } /* rucrcdspl */
