/* mccos.c - Monte Carlo Integral of cos(x) Version 0.1.0            */
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

/***********************************************************/
/* mccos estimates the integral of cos(x) + 1              */
/* using a Monte Carlo simulation.                         */
/* x = uniform random number 0-pi                          */
/* y = uniform random number 0-2                           */
/* n = 1 million                                           */
/* If y < (cos(x) + 1) then tally a counter                */
/* 2 * Pi * the ratio of the (counter / 1 million)         */
/* is approximately Pi to 3 decimal places                 */
/* or approximately 3.141...                               */
/***********************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include "rucrc.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(void)
   {
   int i;                     /* loop counter                 */
   int rucrcelap;             /* elapsed time for rucrc       */
   int mtelap;                /* elapsed time for mt19937     */
   int ranlxelap;             /* elapsed time for ranlxd2     */
   unsigned int dttk;         /* combined date, time #ticks   */
   double tot;                /* total points within a circle */
   double bot;                /* 1 million points             */
   double ratio;              /* estimated 1 / 2pi            */
   time_t now;                /* current date and time        */
   clock_t clk;               /* current number of ticks      */
   clock_t rucrcstart;        /* start time for rucrc         */
   clock_t rucrcfin;          /* end   time for rucrc         */
   clock_t mtstart;           /* start time for mt19937       */
   clock_t mtfin;             /* end   time for mt19937       */
   clock_t ranlxstart;        /* start time for ranlxd2       */
   clock_t ranlxfin;          /* end   time for ranlxd2       */
   struct tms t;              /* structure used by times()    */
   gsl_rng *r;                /* GSL RNG structure            */
   rufmt *ru;                 /* rucrc structure              */
   ru = (rufmt *) rucrcinit();     /* initialize the rucrc structure */
   bot = 1000000.0;           /* set to 1 million             */
   /************************************************************/
   tot = 0.0;                 /* initialize total */
   i = (int) bot;             /* set loop counter */
   /* get clock ticks since boot                           */
   rucrcstart = times(&t);    /* start time for rucrc      */
   while (i--)                /* loop 1 million times      */
      {
      double x;               /* horizontal coordinate        */
      double y;               /* vertical   coordinate        */
      double wyy;             /* y = cos(x) + 1               */
      x = rucrcunif(ru) * M_PI;   /* uniform number 0-pi      */
      y = rucrcunif(ru) * 2.0;      /* uniform number 0-2     */
      wyy = cos(x) + 1.0;           /* the cosine curve */
      if (y < wyy) tot += 1.0;   /* if y is under the curve, tally */
      } /* for each point above or below a cosine curve */
   ratio = 2.0 * M_PI * (tot / bot);     /* calculate est. Pi */
   rucrcfin = times(&t);      /* finish time for rucrc */
   printf("Monte Carlo Definite Integral of cos(x) + 1\n");
   printf("      From zero to Pi\n");
   printf("      Expected error is 1/1000\n");
   printf("      n = 1 million\n");
   printf("      rucrc %18.15f\n", ratio);
   /************************************************************/
   /* allocate the mt19937 random number generator */
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_mt19937);
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL Mersenne Twister                     */
   /* random number generator to date,time,#ticks             */
   gsl_rng_set(r, dttk);      /* initialize mt19937 seed      */
   tot = 0.0;                 /* initialize total */
   i = (int) bot;             /* set loop counter */
   /* get clock ticks since boot                              */
   mtstart = times(&t);       /* start time for GSL mt19937   */
   while (i--)                /* loop 1 million times         */
      {
      double x;               /* horizontal coordinate        */
      double y;               /* vertical   coordinate        */
      double wyy;             /* y = cos(x) + 1               */
      /* use the mt19937 random number generator this time    */
      x = gsl_rng_uniform(r) * M_PI;  /* uniform number 0-pi  */
      y = gsl_rng_uniform(r) * 2.0;   /* uniform number 0-2   */
      wyy = cos(x) + 1.0;           /* the cosine curve */
      if (y < wyy) tot += 1.0;   /* if under the curve, tally */
      } /* for each point above or below a cosine curve */
   ratio = 2.0 * M_PI * tot / bot;   /* calculate est. pi      */
   mtfin = times(&t);         /* finish time for GSL mt19937   */
   printf("GSL mt19937 %18.15f\n", ratio);
   gsl_rng_free(r);
   /************************************************************/
   /* allocate the ranlxd2 random number generator */
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_ranlxd2);
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk);
   /* initialize the GSL ranlxd2 random number generator      */
   /* to date,time,#ticks                                     */
   gsl_rng_set(r, dttk);      /* initialize ranlxd2 seed      */
   tot = 0.0;                 /* initialize total */
   i = (int) bot;             /* set loop counter */
   /* get clock ticks since boot                              */
   ranlxstart = times(&t);    /* start time for GSL ranlxd2   */
   while (i--)                /* loop 1 million times         */
      {
      double x;               /* horizontal coordinate        */
      double y;               /* vertical   coordinate        */
      double wyy;             /* y = cos(x) + 1               */
      /* use the ranlxd2 random number generator this time    */
      x = gsl_rng_uniform(r) * M_PI;   /* uniform number 0-pi */
      y = gsl_rng_uniform(r) * 2.0;    /* uniform number 0-2  */
      wyy = cos(x) + 1.0;           /* the cosine curve */
      if (y < wyy) tot += 1.0;   /* if under the curve, tally */
      } /* for each point above or below a cosine curve */
   ratio = 2.0 * M_PI * (tot / bot);   /* calculate est. pi    */
   ranlxfin = times(&t);      /* finish time for GSL ranlxd2   */
   printf("GSL ranlxd2 %18.15f\n", ratio);
   printf("     Actual %18.15f\n", M_PI);
   rucrcelap = rucrcfin - rucrcstart;
   mtelap    = mtfin    - mtstart;
   ranlxelap = ranlxfin - ranlxstart;
   printf("      rucrc ticks %6d\n", rucrcelap);
   printf("GSL mt19937 ticks %6d\n", mtelap);
   printf("GSL ranlxd2 ticks %6d\n", ranlxelap);
   gsl_rng_free(r);
   free(ru->state);
   free(ru);
   return(0);
   } /* main */
